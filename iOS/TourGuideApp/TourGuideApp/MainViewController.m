//
//  MainViewController.m
//  TourGuideApp
//
//  Created by Cody Geronimo De La Vara on 4/23/13.
//  Copyright (c) 2013 Kin. All rights reserved.
//

#import "MainViewController.h"
#import <MobileCoreServices/MobileCoreServices.h>

@interface MainViewController ()

@end

@implementation MainViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)startCamera:(id)sender
{
    [self startCameraControllerFromViewController:self
                                    usingDelegate:self];
}

- (BOOL)startCameraControllerFromViewController:(UIViewController*) controller
                                  usingDelegate:(id <UIImagePickerControllerDelegate,
                                                 UINavigationControllerDelegate>) delegate {

    if (([UIImagePickerController isSourceTypeAvailable:
          UIImagePickerControllerSourceTypeCamera] == NO)
        || (delegate == nil)
        || (controller == nil))
        return NO;

    UIImagePickerController *cameraUI = [[UIImagePickerController alloc] init];
    cameraUI.sourceType = UIImagePickerControllerSourceTypeCamera;

    // Only enable still picture capture.
    cameraUI.mediaTypes = [[NSArray alloc] initWithObjects: (NSString *) kUTTypeImage, nil];

    // Hides the controls for moving & scaling pictures, or for
    // trimming movies. To instead show the controls, use YES.
    cameraUI.allowsEditing = NO;

    cameraUI.delegate = delegate;

    UIImageView *bottleOverlay = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"beerbox.png"]];
    bottleOverlay.frame = CGRectMake(0, 0, bottleOverlay.image.size.width, bottleOverlay.image.size.height);
    cameraUI.cameraOverlayView = bottleOverlay;

    [controller presentViewController:cameraUI animated:YES completion:nil];
    return YES;
}

// For responding to the user tapping Cancel.
- (void)imagePickerControllerDidCancel: (UIImagePickerController *) picker {
    [[picker presentingViewController] dismissViewControllerAnimated:YES completion:nil];
}

// For responding to the user accepting a newly-captured picture or movie
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info {

    NSString *mediaType = [info objectForKey: UIImagePickerControllerMediaType];
    UIImage *originalImage, *editedImage, *imageToSave;

    // Handle a still image capture
    if (CFStringCompare ((CFStringRef) mediaType, kUTTypeImage, 0)
        == kCFCompareEqualTo) {
//
//        editedImage = (UIImage *) [info objectForKey:
//                                   UIImagePickerControllerEditedImage];
//        originalImage = (UIImage *) [info objectForKey:
//                                     UIImagePickerControllerOriginalImage];
//
//        if (editedImage) {
//            imageToSave = editedImage;
//        } else {
//            imageToSave = originalImage;
//        }
//
//        //_prediction = [self labelImage:imageToSave];
//        NSString *message = [NSString stringWithFormat:@"I think that's a %@ bottle?", _prediction];
//        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Prediction!"
//                                                        message:message
//                                                       delegate:self
//                                              cancelButtonTitle:@"Yep!"
//                                              otherButtonTitles:@"Nope!", nil];
//        [alert show];
    }

    [[picker presentingViewController] dismissViewControllerAnimated:YES completion:nil];
}

@end
