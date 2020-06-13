#ifndef _GFS_USE_
#define _GFS_USE_

// Possible error codes, these are negative to allow
// valid positive return values
enum gfs_error {
    GFS_OK      	= 0,    // No error
    GFS_ERR_DIR      = -2,   // Error during device operation
	GFS_ERR_NORD_PER= -4,	// No write permission
	GFS_ERR_NOWR_PER= -5,	// No write permission
	GFS_ERR_LEN		= -7,	// No write permission
    GFS_ERR_CORRUPT = -52,  // Corrupted
    GFS_ERR_NOENT   = -2,   // No directory entry
    GFS_ERR_EXIST   = -17,  // Entry already exists
    GFS_ERR_NOTDIR  = -20,  // Entry is not a dir
    GFS_ERR_ISDIR   = -21,  // Entry is a dir
    GFS_ERR_INVAL   = -22,  // Invalid parameter
    GFS_ERR_NOSPC   = -28,  // No space left on device
    GFS_ERR_NOMEM   = -12,  // No more memory available
};

// File open flags
enum gfs_open_flags {
    // open flags
    F_RDONLY = 1,        // Open a file as read only
    F_WRONLY = 2,        // Open a file as write only
    F_RDWR   = 3,        // Open a file as read and write
    F_CREAT  = 0x0100,   // Create a file if it does not exist
    F_CRNEW  = 0x0200,   // Truncate the existing file to zero size
    F_APPEND = 0x0400,   // Move to end of file on every write
    F_ENC 	 = 0x0800,   // Encrypt file
};
// File seek flags
enum lfs_whence_flags {
    F_SEEK_SET = 0,   // Seek relative to an absolute position
    F_SEEK_CUR = 1,   // Seek relative to the current file position
    F_SEEK_END = 2,   // Seek relative to the end of the file
};




/*
gFILE* pFd_gfs=NULL;
pFd_gfs=gfs_open("pathname",GFS_O_RDWR);
ret=gfs_write(pFd_gfs,(u8*)pInPar->pStr,pInPar->Len);
ret=gfs_read(pFd_gfs,(u8*)pData,pInPar->Len);
ret = gfs_seek(pFd_gfs, pInPar->uData, pInPar->pNext->uData);
ret=gfs_close(pFd_gfs);
ret=gfs_remove(pInPar->pStr);


*/

typedef struct  
{
	char	Mask[4];			// "gfs"
	void* (*open)(const char*, int,...);	//(const char *path, int flags ,...)
	int (*close)(void*);				//(void* pfd)
	int (*seek)(void*,int, int);	//(void* pfd,int offset, int whence)
	int (*read)(void*,void *,int);	//(void* pfd,void *buff,int size)
	int (*write)(void*,void *,int); //(void* pfd,void *buff,int writeLen)
	int (*getSize)(void*);			//(void* pfd)
	int (*readSize)(const char*);	//(const char *path)
	int (*remove)(const char*);		//(const char *path)
	
	int (*fileFomat)(const char*);	//(const char* pKey)
	//--后进先出 队列记录器，独立FLASH操作文件系统之外-------------------
	int (*LifoRecordInit)(void *,int);	//(void *pData,int size)
	int (*LifoRecordRead)(void *,int);	//(void *pData,int Index)
	int (*LifoRecordWrite)(void *);		//(void *pData)
}API_FILE_Def;
extern API_FILE_Def*		pFileFun;
//=============证通文件系统接口========================
#define gFILE void*
//typedef		(void*)		gFILE;			
#define API_fopen(name,flag,...) 	pFileFun->open(name,flag,## __VA_ARGS__)
#define API_fclose(fd)				pFileFun->close(fd)
#define API_fseek(fd,offset,whence)	pFileFun->seek(fd,offset,whence)
#define API_fread(fd,buf,count)		pFileFun->read(fd,buf,count)
#define API_fwrite(fd,buf,count)	pFileFun->write(fd,buf,count)
#define API_fremove(name)			pFileFun->remove(name)
#define API_fsize(name)				pFileFun->readSize(name)

#define API_fgsize(fd)				pFileFun->getSize(fd)

#endif
