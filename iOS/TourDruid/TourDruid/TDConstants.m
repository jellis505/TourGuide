//
//  TDConstants.m
//  TourDruid
//
//  Created by Cody Geronimo De La Vara on 5/3/13.
//  Copyright (c) 2013 Kin. All rights reserved.
//

#import "TDConstants.h"
#import <UIKit/UIKit.h>

@implementation TDConstants
NSArray *_names;
NSArray *_images;

+ (void) buildNames
{
    _names = [[NSArray alloc ] initWithObjects:@"Alma Mater" ,@"Butler", @"CEPSR", @"CURL", @"Hamilton",   @"Havemayer", @"Journalism", @"Law", @"Lerner", @"Lion", @"Low", @"Mathematics", @"Mudd", @"Noco", @"Pan", @"Pupin", @"Thinker", nil];
}

+ (void) buildImages
{
    NSArray *imageNames = [[NSArray alloc ] initWithObjects:@"almamater1.jpg" ,@"butler1.jpg", @"CEPSR1.jpg", @"curl1.jpg", @"hamilton.jpg",   @"havemayer.jpg", @"journalism1.jpg", @"law1.png", @"lerner1.JPG", @"lion1.jpg", @"low1.jpg", @"mathematics1.jpg", @"mudd1.jpg", @"noco1.jpg", @"pan1.JPG", @"Pupin", @"Thinker", nil];

    NSMutableArray *tmp_images = [[NSMutableArray alloc] init];
    for (NSString *name in imageNames) {
        [tmp_images addObject:[UIImage imageNamed:name]];
    }
    _images = [[NSArray alloc] initWithArray:tmp_images];
}

+ (NSString *)nameFromId:(NSNumber *)buildingID
{
    if (_names == nil) {
        [self buildNames];
    }

    if ([buildingID integerValue] > [_names count]) {
        return nil;
    } else
        return (NSString *)[_names objectAtIndex:[buildingID integerValue]];
}

+ (UIImage *) imageFromId:(NSNumber *)imageId
{
    if (_images == nil) {
        [self buildImages];
    }

    if ([imageId integerValue] > [_images count]) {
        return nil;
    } else
        return (UIImage *)[_images objectAtIndex:[imageId integerValue]];
}

+ (NSInteger)numberOfBuildings
{
    if(_names == nil) {
        [self buildNames];
    }
    return [_names count];
}
@end
