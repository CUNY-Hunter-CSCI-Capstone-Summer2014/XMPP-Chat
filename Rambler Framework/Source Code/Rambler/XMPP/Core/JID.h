/**********************************************************************************************************************
 * @file    Rambler/XMPP/Core/JID.h
 * @date    2014-07-09
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#import <Foundation/Foundation.h>

/**
 * An object that represents a Jabber ID (JID). It is immutable.
 * @author Omar Stefan Evans
 * @date   2014-07-09
 */
@interface JID : NSObject

@property (nonatomic, strong, readonly) NSString * localPart;
@property (nonatomic, strong, readonly) NSString * domainPart;
@property (nonatomic, strong, readonly) NSString * resourcePart;
@property (nonatomic, strong, readonly) JID * bareJID;
@property (nonatomic, assign, readonly) BOOL isBareJID;
@property (nonatomic, assign, readonly) BOOL isBareJIDWithLocalPart;
@property (nonatomic, assign, readonly) BOOL isFullJID;
@property (nonatomic, assign, readonly) BOOL isFullJIDWithLocalPart;
@property (nonatomic, assign, readonly) BOOL isDomainJID;
@property (nonatomic, assign, readonly, getter=isValid) BOOL valid;

/**
 * A designated initializer
 * @author  Omar Stefan Evans
 * @date    2014-07-09
 */
- (instancetype)initWithLocalPart:(NSString *)aLocalPart
                      domainPart:(NSString *)aDomainPart
                    resourcePart:(NSString *)aResourcePart;

/**
 * A convenience initializer
 * @author  Omar Stefan Evans
 * @date    2014-07-09
 */
- (instancetype)initWithLocalPart:(NSString *)aLocalPart
                      domainPart:(NSString *)aDomainPart;

/**
 * A convenience initializer
 * @author  Omar Stefan Evans
 * @date    2014-07-09
 */
- (instancetype)initWithDomainPart:(NSString *)aDomainPart;

/**
 * A convenience initializer
 * @author  Omar Stefan Evans
 * @date    2014-07-09
 */
- (instancetype)initWithDomainPart:(NSString *)aDomainPart
                     resourcePart:(NSString *)aResourcePart;

/**
 * Returns a printable JID string
 * @author  Omar Stefan Evans
 * @date    2014-07-09
 * @details A full JID is printed as localPart@domainPart/resourcePart, or as domainPart/resourcePart for domain JIDs.
 *          A bare JID is printed as localPart@domainPart, or as domainPart for domain JIDs.
 */
- (NSString *)description;


@end