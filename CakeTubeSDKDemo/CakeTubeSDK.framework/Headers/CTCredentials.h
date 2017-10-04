//
// Created by Igor Glotov on 22/02/15.
// Copyright (c) 2015 AnchorFree. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CTCredentials : NSObject
@property(strong, nonatomic) NSString *result;
@property(strong, nonatomic) NSString *error;

@property(strong, nonatomic) NSString *name;
@property(strong, nonatomic) NSString *country;
@property(strong, nonatomic) NSString *ip;
@property(strong, nonatomic) NSString *port;
@property(strong, nonatomic) NSString *protocol;
@property(strong, nonatomic) NSString *username;
@property(strong, nonatomic) NSString *password;

@property(strong, nonatomic) NSNumber *expireTime;
@property(strong, nonatomic) NSNumber *createTime;

+ (CTCredentials *)fromDict:(NSDictionary *)dict;

- (NSString *)description;

- (NSDictionary *)toDict;
@end
