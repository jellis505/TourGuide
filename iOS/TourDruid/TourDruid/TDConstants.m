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
NSDictionary *_images;

+ (void) buildNames
{
    _names = [[NSArray alloc ] initWithObjects:@"Alma Mater" ,@"Butler Library", @"CEPSR", @"Curl", @"Hamilton",   @"Havemayer", @"Journalism", @"Law", @"Lerner", @"Lion", @"Low", @"Mathematics", @"Mudd", @"Noco", @"Pan", @"Pupin", @"Thinker", nil];
}

+ (void) buildImages
{
    if (_names == nil) {
        [self buildNames];
    }
    
    NSArray *imageNames = [[NSArray alloc ] initWithObjects:@"almamater1.jpg" ,@"butler1.jpg", @"CEPSR1.jpg", @"curl1.jpg", @"hamilton1.jpg",   @"havemayer.png", @"journalism1.jpg", @"law1.png", @"lerner1.JPG", @"lion1.jpg", @"low1.jpg", @"mathematics1.jpg", @"mudd1.jpg", @"noco1.jpg", @"pan1.JPG", @"pupin1.png", @"thinker1.jpg", nil];

    NSMutableArray *tmp_images = [[NSMutableArray alloc] init];
    for (NSString *name in imageNames) {
        NSLog(@"yes");
        [tmp_images addObject:[UIImage imageNamed:name]];
    }
    _images = [[NSDictionary alloc] initWithObjects:tmp_images forKeys:_names];
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

+ (UIImage *) imageFromName:(NSString *)building
{
    if (_images == nil) {
        [self buildImages];
    }


    return (UIImage *)[_images objectForKey:building];
}

+ (UIImage *) imageFromId:(NSNumber *)buildingId
{
    if (_images == nil) {
        [self buildImages];
    }


    return (UIImage *)[_images objectForKey:(NSNumber *)[_names objectAtIndex:[buildingId integerValue]]];
}

+ (NSInteger)numberOfBuildings
{
    if(_names == nil) {
        [self buildNames];
    }
    return [_names count];
}
@end
