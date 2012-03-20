//
//  DKFile.h
//  DataKit
//
//  Created by Erik Aigner on 13.03.12.
//  Copyright (c) 2012 chocomoko.com. All rights reserved.
//

#import <Foundation/Foundation.h>


typedef void (^DKFileSaveResultBlock)(BOOL success, NSError *error);
typedef void (^DKFileLoadResultBlock)(NSData *data, NSError *error);
typedef void (^DKFileDeleteResultBlock)(BOOL success, NSError *error);
typedef void (^DKFileExistsResultBlock)(BOOL exists, NSError *error);

/**
 Block to track download and upload progress
 
 @param bytes Bytes received or written
 @param totalBytes Total expected bytes
 */
typedef void (^DKFileProgressBlock)(NSUInteger bytes, NSUInteger totalBytes);

/**
 Represents a block of binary data. You should use this class for larger data objects (>10MB).
 */
@interface DKFile : NSObject
@property (nonatomic, assign, readonly) BOOL isVolatile;
@property (nonatomic, copy, readonly) NSURL *URL;
@property (nonatomic, copy, readonly) NSString *name;

/** @name Creating Files */

/**
 Creates a new file with the given data and name.
 
 The file name must be unique, otherwise save will return an error.
 @param data The file data
 @param name The file name, if `nil` the server will assign a random name.
 @return The initialized file
 */
+ (DKFile *)fileWithData:(NSData *)data name:(NSString *)name;

/**
 Initializes a new file with the given data and name.
 
 The file name must be unique, otherwise save will return an error.
 @param data The file data
 @param name The file name, if `nil` the server will assign a random name.
 @return The initialized file
 */
- (id)initWithData:(NSData *)data name:(NSString *)name;

/** @name Checking Existence */

/**
 Checks if a file with the specified name exists.
 @param fileName The file name to check
 @return `YES` if the file exists, `NO` if it doesn't
 */
+ (BOOL)fileExists:(NSString *)fileName;

/**
 Checks if a file with the specified name exists.
 @param fileName The file name to check
 @param error The error object set on error
 @return `YES` if the file exists, `NO` if it doesn't
 */
+ (BOOL)fileExists:(NSString *)fileName error:(NSError **)error;

/**
 Checks if a file with the specified name exists in the background
 @param fileName The file name to check
 @param block The result callback
 */
+ (void)fileExists:(NSString *)fileName inBackgroundWithBlock:(DKFileExistsResultBlock)block;

/** @name Deleting Files */

/**
 Deletes the specified file
 @param fileName The file name
 @param error The error object set on error
 @return `YES` if the file was deleted, `NO` if not
 */
+ (BOOL)deleteFile:(NSString *)fileName error:(NSError **)error;

/**
 Deletes the specified files
 @param fileNames The file names
 @param error The error object set on error
 @return `YES` if the files were deleted, `NO` if not
 */
+ (BOOL)deleteFiles:(NSArray *)fileNames error:(NSError **)error;

/**
 Deletes the current file
 @return `YES` if the file was deleted, `NO` if not
 */
- (BOOL)delete;

/**
 Deletes the current file
 @param error The error object set on error
 @return `YES` if the file was deleted, `NO` if not
 */
- (BOOL)delete:(NSError **)error;

/**
 Deletes the current file in the background
 @param block The result callback
 */
- (void)deleteInBackgroundWithBlock:(DKFileDeleteResultBlock)block;

/** @name Saving Files */

/**
 Saves the current file
 @return `YES` if the file was saved, otherwise `NO`.
 */
- (BOOL)save;

/**
 Saves the current file
 @param error The error object set on error
 @return `YES` if the file was saved, otherwise `NO`.
 */
- (BOOL)save:(NSError **)error;

/**
 Saves the current file in the background
 @param block The result block
 */
- (void)saveInBackgroundWithBlock:(DKFileSaveResultBlock)block;

/**
 Saves the current file in the background and tracks upload progress
 @param block The result callback
 @param progressBlock The progress callback for tracking upload progress
 */
- (void)saveInBackgroundWithBlock:(DKFileSaveResultBlock)block progressBlock:(DKFileProgressBlock)progressBlock;

/** @name Loading Data */

- (NSData *)loadData;
- (NSData *)loadData:(NSError **)error;
- (void)loadDataInBackgroundWithBlock:(DKFileLoadResultBlock)block;
- (void)loadDataInBackgroundWithBlock:(DKFileLoadResultBlock)block progressBlock:(DKFileProgressBlock)progressBlock;

/** @name Aborting */

- (void)abort;

@end