#include <windows.h>
#include <stdio.h>
#include <ntsecapi.h>
#include <sspi.h>
#include <schnlsp.h>
#pragma comment(lib, "crypt32.lib")

#define MACHINE_NAME "example server"
namespace SecUtilities{

	/**
	* DOMAIN NAME FOR CREDEINTIALS
	* SPECIFY IF U HAVE ANY CREDENTIALS
	* CREDENTIALS FOR SERVER and FOR YOURSELF
	* Create Security Context
	* Start Handshake
	*/




void getSchannelClientHandle(PCredHandle ppClientCred)
{
  SECURITY_STATUS SecStatus;
  TimeStamp Lifetime;
  CredHandle hCred;
  SCHANNEL_CRED credData;

  ZeroMemory(&credData, sizeof(credData));
  credData.dwVersion = SCHANNEL_CRED_VERSION;

  //-------------------------------------------------------
  // Specify the TLS V1.0 (client-side) security protocol.
  credData.grbitEnabledProtocols = SP_PROT_TLS1_2_CLIENT;
    
  SecStatus = AcquireCredentialsHandle (
       NULL,                  // default principal
       UNISP_NAME,            // name of the SSP
       SECPKG_CRED_OUTBOUND,  // client will use the credentials
       NULL,                  // use the current LOGON id
       &credData,             // protocol-specific data
       NULL,                  // default
       NULL,                  // default
       &hCred,                // receives the credential handle
       &Lifetime              // receives the credential time limit
  );
  printf("Client credentials status: 0x%x\n", SecStatus);
  // Return the handle to the caller.
  if(ppClientCred != NULL)
      *ppClientCred = hCred;

  return;
  //-------------------------------------------------------
  // When you have finished with this handle,
  // free the handle by calling the 
  // FreeCredentialsHandle function.
}


PCCERT_CONTEXT getServerCertificate()
{
	HCERTSTORE hMyCertStore = NULL;
	PCCERT_CONTEXT aCertContext = NULL;

	//-------------------------------------------------------
	// Open the My store, also called the personal store.
	// This call to CertOpenStore opens the Local_Machine My 
	// store as opposed to the Current_User's My store.

	hMyCertStore = CertOpenStore(CERT_STORE_PROV_SYSTEM,
		X509_ASN_ENCODING,
		0,
		CERT_SYSTEM_STORE_LOCAL_MACHINE,
		L"MY");

	if (hMyCertStore == NULL)
	{
		printf("Error opening MY store for server.\n");
		goto cleanup;
	}
	//-------------------------------------------------------
	// Search for a certificate with some specified
	// string in it. This example attempts to find
	// a certificate with the string "example server" in
	// its subject string. Substitute an appropriate string
	// to find a certificate for a specific user.

	aCertContext = CertFindCertificateInStore(hMyCertStore,
		X509_ASN_ENCODING,
		0,
		CERT_FIND_SUBJECT_STR_A,
		MACHINE_NAME, // use appropriate subject name
		NULL
		);

	if (aCertContext == NULL)
	{
		printf("Error retrieving server certificate.");
		goto cleanup;
	}
cleanup:
	if (hMyCertStore)
	{
		CertCloseStore(hMyCertStore, 0);
	}
	return aCertContext;
}

}