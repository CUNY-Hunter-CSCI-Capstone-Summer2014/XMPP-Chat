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
 * An object that represents a Jabber ID (JID). It is immutable.
 * @author Omar Stefan Evans
 * @date   2014-07-09
 */
@interface JID : NSObject <NSCopying>

@property (nonatomic, strong, readonly) NSString * localPart;
@property (nonatomic, strong, readonly) NSString * domainPart;
@property (nonatomic, strong, readonly) NSString * resourcePart;
@property (nonatomic, strong, readonly) JID * bareJID;
@property (nonatomic, assign, readonly) BOOL isBareJID;
@property (nonatomic, assign, readonly) BOOL isBareJIDWithLocalPart;
@property (nonatomic, assign, readonly) BOOL isFullJID;
@property (nonatomic, assign, readonly) BOOL isFullJIDWithLocalPart;
@property (nonatomic, assign, readonly) BOOL isDomainJID;

/**
 * A designated initializer
 * @author  Omar Stefan Evans
 * @date    2014-07-10
 */
- (instancetype)initWithString:(NSString *)aString NS_DESIGNATED_INITIALIZER;

/**
 * A designated initializer
 * @author  Omar Stefan Evans
 * @date    2014-07-09
 */
- (instancetype)initWithLocalPart:(NSString *)aLocalPart
                      domainPart:(NSString *)aDomainPart
                    resourcePart:(NSString *)aResourcePart NS_DESIGNATED_INITIALIZER;

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
 * Implements the NSCopying protocol.
 * @author  Omar Stefan Evans
 * @date    2014-07-10
 * @details Since this object is immutable, it simply returns self.
 */
- (id)copyWithZone:(NSZone *)zone;

/**
 * The string representation for this JID
 * @author  Omar Stefan Evans
 * @date    2014-07-09
 * @details A full JID is printed as localPart@domainPart/resourcePart, or as domainPart/resourcePart for domain JIDs.
 *          A bare JID is printed as localPart@domainPart, or as domainPart for domain JIDs.
 */
- (NSString *)description;

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