//
// Created by Igor Glotov on 05/03/15.
// Copyright (c) 2015 AnchorFree. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CTServerLocation;

@interface CTServersResponse : NSObject

@property(strong, nonatomic) NSString *result;
@property(strong, nonatomic) NSString *error;

@property(strong, nonatomic) NSArray<CTServerLocation *> *servers;

+ (CTServersResponse *)fromDict:(NSDictionary *)dict;
@end
