//
// Created by Igor Glotov on 22/02/15.
// Copyright (c) 2015 AnchorFree. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CTVerifyResponse : NSObject

@property(strong, nonatomic) NSString *result;

+ (CTVerifyResponse *)fromDict:(NSDictionary *)dict;
@end

