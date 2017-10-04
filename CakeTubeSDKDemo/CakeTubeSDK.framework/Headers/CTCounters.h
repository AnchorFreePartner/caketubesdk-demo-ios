//
// Created by Igor Glotov on 06/03/15.
// Copyright (c) 2015 AnchorFree. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CTCounters : NSObject

@property(strong, nonatomic) NSString *error;
@property(strong, nonatomic) NSString *result;
@property(strong, nonatomic) NSNumber *tx;
@property(strong, nonatomic) NSNumber *rx;

+ (CTCounters *)fromDict:(NSDictionary *)dict;
@end
