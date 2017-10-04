//
// Created by Igor Glotov on 11/03/15.
// Copyright (c) 2015 AnchorFree. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CTBundle : NSObject

@property(strong, nonatomic) NSNumber *devicesLimit;
@property(strong, nonatomic) NSNumber *sessionsLimit;
@property(strong, nonatomic) NSNumber *sid;
@property(strong, nonatomic) NSString *name;

- (NSString *)description;

@end
