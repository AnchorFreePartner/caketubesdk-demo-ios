//
//  CTConnectionService.h
//  CakeTubeSDK
//
//  Created by Valentin Shergin on 17/02/15.
//  Copyright (c) 2015 AnchorFree. All rights reserved.
//

#import "CTConnectionServiceBase.h"

@class CTServerLocation;


@interface CTConnectionService : CTConnectionServiceBase

- (void)connectVPNWithCompletion:(void (^)(CTServerLocation *location, NSError *error))completion;
@end
