//
//  DKObject+Private.h
//  DataKit
//
//  Created by Erik Aigner on 26.02.12.
//  Copyright (c) 2012 chocomoko.com. All rights reserved.
//

#import "DKObject.h"

@interface DKObject () // CLS_EXT
@property (nonatomic, copy, readwrite) NSString *entityName;
@property (nonatomic, strong) NSMutableDictionary *requestMap;
@property (nonatomic, strong) NSDictionary *resultMap;
@end

@interface DKObject (Private)

- (BOOL)commitObjectResultMap:(NSDictionary *)resultMap error:(NSError **)error;

@end