//
//  ViewController.h
//  TourDruid
//
//  Created by Cody Geronimo De La Vara on 4/23/13.
//  Copyright (c) 2013 Kin. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController<UIImagePickerControllerDelegate,
UINavigationControllerDelegate>
-(IBAction)takePhoto :(id)sender;
@end
