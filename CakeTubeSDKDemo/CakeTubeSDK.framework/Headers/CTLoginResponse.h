//
// Created by Igor Glotov on 22/02/15.
// Copyright (c) 2015 AnchorFree. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CTBundle;
@class CTUserProfile;


@interface CTLoginResponse : NSObject
@property(strong, nonatomic) NSString *result;
@property(strong, nonatomic) NSString *error;
@property(strong, nonatomic) NSString *accessToken;
@property(strong, nonatomic) CTUserProfile *subscriber;

+ (CTLoginResponse *)fromDict:(NSDictionary *)dict;

- (NSDictionary *)toDict;

- (NSString *)description;

@end

