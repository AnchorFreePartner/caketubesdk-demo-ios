//
//  CakeTubeSDK.h
//  CakeTubeSDK
//
//  Copyright (c) 2015 AnchorFree. All rights reserved.
//

#import <Foundation/Foundation.h>

//! Project version number for CakeTubeSDK.
FOUNDATION_EXPORT double CakeTubeSDKVersionNumber;

//! Project version string for CakeTubeSDK.
FOUNDATION_EXPORT const unsigned char CakeTubeSDKVersionString[];


// All Public Headers
#import "CakeTube.h"
#import "CTConstants.h"
#import "CTAuthMethod.h"
#import "CTClientService.h"
#import "CTCounters.h"
#import "CTServerLocation.h"
#import "CTUserProfile.h"
#import "CTLoginResponse.h"
#import "CTBundle.h"
#import "CTVerifyResponse.h"
#import "CTRemainingTraffic.h"

#pragma - Platform specific

#if TARGET_OS_IPHONE

#pragma - iOS Specific Headers

#import "CTConnectionService.h"

#else

#pragma - OS X Specific Headers

#import "CTConnectionService.h"
#import "CTOpenVPNLauncher.h"
#import "CTOpenVPNManager.h"
#import "CTHelper.h"
#import "CTHelperManager.h"

#endif
