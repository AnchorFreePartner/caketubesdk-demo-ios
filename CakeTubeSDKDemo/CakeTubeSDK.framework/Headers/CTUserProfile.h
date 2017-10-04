//
// Created by Igor Glotov on 11/03/15.
// Copyright (c) 2015 AnchorFree. All rights reserved.
//

#import <Foundation/Foundation.h>


@class CTBundle;

@interface CTPurchaseInfo : NSObject

@property(strong, nonatomic) NSString *identifier;
@property(strong, nonatomic) NSString *type;
@property(strong, nonatomic) NSString *checkTime;

@end

@interface CTUserProfile : NSObject

@property(strong, nonatomic) NSString *locale;
@property(strong, nonatomic) NSString *name;
@property(strong, nonatomic) NSDictionary *socialProfiles;
@property(strong, nonatomic, readonly) NSString *email;
@property(strong, nonatomic) NSString *registrationTime;
@property(strong, nonatomic) NSString *connectionTime;
@property(strong, nonatomic) NSNumber *condition;
@property(strong, nonatomic) NSNumber *activatedDevices;
@property(strong, nonatomic) NSNumber *activeSessions;
@property(strong, nonatomic) NSString *authMethod;

@property(strong, nonatomic) CTBundle *bundle;
@property(strong, nonatomic) NSArray *purchases;

- (NSString *)description;

- (NSDictionary *)toDict;

+ (CTUserProfile *)fromDict:(NSDictionary *)dict;

@end

@interface CTSubscriberResponse : NSObject

@property(strong, nonatomic) NSString *result;
@property(strong, nonatomic) NSString *error;
@property(strong, nonatomic) CTUserProfile *subscriber;

+ (CTSubscriberResponse *)fromDict:(NSDictionary *)dict;
@end
