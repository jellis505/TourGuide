//
//  MapViewController.h
//  TourDruid
//
//  Created by Cody Geronimo De La Vara on 5/11/13.
//  Copyright (c) 2013 Kin. All rights reserved.
//

#import <UIKit/UIKit.h>
@class InfoViewController;
@interface MapViewController : UIViewController
@property (weak, nonatomic) IBOutlet UIImageView *mapImage;
@property (nonatomic) InfoViewController *infoView;
- (void) setImage:(UIImage *)image;
@end
