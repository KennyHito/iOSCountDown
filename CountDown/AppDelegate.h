//
//  AppDelegate.h
//  CountDown
//
//  Created by 于海涛 on 16/12/5.
//  Copyright © 2016年 Hito. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreData/CoreData.h>

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

@property (readonly, strong) NSPersistentContainer *persistentContainer;

- (void)saveContext;


@end

