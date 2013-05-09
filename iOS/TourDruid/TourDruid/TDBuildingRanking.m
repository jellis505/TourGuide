//
//  TDBuildingRanking.m
//  TourDruid
//
//  Created by Cody Geronimo De La Vara on 5/3/13.
//  Copyright (c) 2013 Kin. All rights reserved.
//

#import "TDBuildingRanking.h"
#import "TDConstants.h"

@implementation TDBuildingRanking

- (id) init:(NSNumber *)buildingID {
    self = [super init];
    if (self) {
        
    }
    _buildingId = buildingID;
    _name = [TDConstants nameFromId:buildingID];
    return self;
}


@end
