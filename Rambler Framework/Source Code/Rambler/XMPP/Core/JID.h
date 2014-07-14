/**********************************************************************************************************************
 * @file    Rambler/XMPP/Core/JID.h
 * @author  Omar Stefan Evans
 * @author  Peter Kamaris
 * @date    2014-07-10
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#import <Foundation/Foundation.h>

/**
 * An object that represents a Jabber ID (JID). It is immutable. Thread safety is guaranteed.
 * @author Omar Stefan Evans
 * @author Peter Kamaris
 * @date   2014-07-12
 */
@interface JID : NSObject <NSCopying>

#pragma mark Properties

/**
 * Returns a String that represents the local part of this JID as defined by RFC 6122.
 * This property is automatically synthesized by the compiler.
 * @date    2014-07-12
 * @return  a String representing the local part of this JID
 */
@property (readonly, strong) NSString * localPart;

/**
 * Returns a String that represents the domain part of this JID as defined by RFC 6122.
 * This property is automatically synthesized by the compiler.
 * @date    2014-07-12
 * @return  a String representing the domain part of this JID
 */
@property (readonly, strong) NSString * domainPart;

/**
 * Returns a String that represents the resource part of this JID as defined by RFC 6122.
 * This property is automatically synthesized by the compiler.
 * @date    2014-07-12
 * @return  a String representing the resource part of this JID
 */
@property (readonly, strong) NSString * resourcePart;

/**
 * Returns a "bare JID", as defined by RCF 6122, that is derived from this one.
 * @author  Omar Stefan Evans
 * @date    2014-07-10
 * @return  a bare JID that is derived from this one
 * @details the returned JID may be identical to this one
 */
@property (readonly, strong) JID * bareJID;

/**
 * Returns the string representation for this JID
 * @author  Omar Stefan Evans
 * @date    2014-07-09
 * @return  the string representation of this JID
 * @details A full JID is printed as localPart@domainPart/resourcePart, or as domainPart/resourcePart for domain JIDs.
 *          A bare JID is printed as localPart@domainPart, or as domainPart for domain JIDs.
 */
@property (readonly, strong) NSString *description;

/**
 * Returns a Boolean value that indicates whether this JID is a "bare JID" as defined by RFC 6120.
 * @author  Peter Kamaris
 * @date    2014-07-10
 * @return  YES if and only if this JID is a "bare JID"
 */
@property (readonly, assign) BOOL isBareJID;

/**
 * Returns a Boolean value that indicates whether this JID is a "bare JID" as defined by RFC 6120,
 * which additionally has a local part, as defined by RFC 6122.
 * @author  Peter Kamaris
 * @date    2014-07-10
 * @return  YES if and only if this JID is a "bare JID" which has a local part
 */
@property (readonly, assign) BOOL isBareJIDWithLocalPart;

/**
 * Returns a  Boolean value that indicates whether this JID is a "full JID" as defined by RFC 6120.
 * @author  Peter Kamaris
 * @date    2014-07-10
 * @return  YES if and only if this JID is a "full JID"
 */
@property (readonly, assign) BOOL isFullJID;

/**
 * Returns a Boolean value that indicates whether this JID is a "full JID" as defined by RFC 6120,
 * which additionally has a local part, as defined by RFC 6122.
 * @author  Peter Kamaris
 * @date    2014-07-10
 * @return  YES if and only if this JID is a "full JID" which has a local part
 */
@property (readonly, assign) BOOL isFullJIDWithLocalPart;

/**
 * Returns a Boolean value that indicates whether this JID lacks a local part, as defined by RFC 6122.
 * @author  Peter Kamaris
 * @date    2014-07-10
 * @return  YES if and only if this JID is a JID which lacks a local part
 */
@property (readonly, assign) BOOL isDomainJID;



#pragma mark Initializers

/**
 * A convenience initializer
 * @author  Omar Stefan Evans
 * @date    2014-07-10
 */
- (instancetype)initWithString:(NSString *)aString;

/**
 * A convenience initializer
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



#pragma mark Methods

/**
 * Implements the NSCopying protocol.
 * @author  Omar Stefan Evans
 * @date    2014-07-10
 * @details Since this object is immutable, it simply returns self.
 */
- (id)copyWithZone:(NSZone *)zone;

/**
 * The hash value for this JID
 * @author  Omar Stefan Evans
 * @date    2014-07-10
 * @details returns the hash value of this JID's string representation
 * @see     description
 */
- (NSUInteger)hash;

/**
 * Overrides the default implementation in NSObject
 * @author  Omar Stefan Evans
 * @date    2014-07-10
 * @details returns YES if object is another JID and the JIDs are equal
 * @see     isEqualToJID:
 */
- (BOOL)isEqual:(id)object;

/**
 * Compares two JIDs for equality
 * @author  Omar Stefan Evans
 * @date    2014-07-10
 * @details Two JIDs are equal if their string representations are the same
 * @see     description
 */
- (BOOL)isEqualToJID:(JID *)aJID;



@end