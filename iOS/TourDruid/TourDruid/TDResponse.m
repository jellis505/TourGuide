//
//  TDResponse.m
//  TourDruid
//
//  Created by Cody Geronimo De La Vara on 5/3/13.
//  Copyright (c) 2013 Kin. All rights reserved.
//

#import "TDResponse.h"

@implementation TDResponse

-(id)init:(NSArray *)ranking requestID:(NSString *)classifyID
{
    self = [super init];
    if (self) {
        _ranking = ranking;
        _classifyID = classifyID;
    }
    return self;
}

@end
