//
//  MainViewController.h
//  TourGuideApp
//
//  Created by Cody Geronimo De La Vara on 4/23/13.
//  Copyright (c) 2013 Kin. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface MainViewController : UIViewController <UIImagePickerControllerDelegate, UINavigationControllerDelegate, UIAlertViewDelegate> {
}

- (IBAction)startCamera:(id)sender;
//- (NSString *)labelImage:(UIImage *)image;

@end