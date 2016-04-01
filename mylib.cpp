#include "mylib.h"

static void con() __attribute__((constructor));
static void dec() __attribute__((destructor));

void con() 
{
    output_file = stderr;
    dprintf(WARN, "initial debug output file\n");

    output_file = fopen(ACTUAL_FILE_NAME,"w");

    if(output_file == NULL)
    {
        output_file = stderr;
        dprintf(WARN, "due to open file failed, stderr is debug message output file now");
    }
}

void dec()
{
    if(output_file!=stderr);
        fclose(output_file);
}

template<typename FUNC_T>
FUNC_T get_func_ptr(const char* lib_name, const char* func_name)
{
    void* lib_handle = dlopen(lib_name,RTLD_LAZY);
    if(!lib_handle) dprintf(ERROR, "open %s error",lib_name);

    FUNC_T fp = (FUNC_T)dlsym(lib_handle,func_name);

    if(!fp)
        dprintf(ERROR, "find symbol %s from %s error",func_name,lib_name);

    return fp;
}

extern "C" int mkdir(const char *pathname, mode_t mode)
{
    using mkdir_ft = int (*)(const char*,mode_t);

    dprintf(INFO, "'%s'\n",pathname);

    return get_func_ptr<mkdir_ft>(GLIBC_SO, "mkdir")(pathname,mode);
}

extern "C" FILE *fopen64(const char *filename, const char *type)
{
    using fopen64_ft = FILE* (*)(const char*,const char*);

    dprintf(INFO, "'%s' (%s)\n",filename,type);

    return get_func_ptr<fopen64_ft>(GLIBC_SO, "fopen64")(filename,type);
}

extern "C" int getaddrinfo(const char *node, const char *service,
        const struct addrinfo *hints,
        struct addrinfo **res)
{
    using getai_ft = int (*)(const char*,const char*,const struct addrinfo*,struct addrinfo**);

    dprintf(INFO, "connect to '%s' by %s\n",node,service);

    auto ret = get_func_ptr<getai_ft>(GLIBC_SO, "getaddrinfo")(node,service,hints,res);

    struct addrinfo* p;
    for(p = *res;p != NULL; p = p->ai_next) {
        void *addr;
        char *ipver;
        char ipstr[INET6_ADDRSTRLEN];

        if (p->ai_family == AF_INET) { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } else { // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        dprintf(DEBUG, "Available addr %s: %s\n", ipver, ipstr);
    }

    return ret;
}

extern "C" size_t fread ( void * ptr, size_t size, size_t count, FILE * stream )
{
    using fr_t = size_t (*)(void*,size_t,size_t,FILE*);

    auto ret = get_func_ptr<fr_t>(GLIBC_SO, "fread")(ptr,size,count,stream);

    char filePath[PATH_MAX] = {};
    char fileName[PATH_MAX] = {};
    sprintf(filePath, "/proc/self/fd/%d", fileno(stream));
    if(-1 != readlink(filePath,fileName,255))
        dprintf(INFO, "total %lu elements read from %s\n", ret,fileName);
    else
        dprintf(INFO, "total %lu elements read\n", ret);

    return ret;
}

extern "C" size_t fwrite ( const void * ptr, size_t size, size_t count, FILE * stream )
{
    using fw_t = size_t (*)(const void*,size_t,size_t,FILE*);

    auto ret = get_func_ptr<fw_t>(GLIBC_SO, "fwrite")(ptr,size,count,stream);

    char filePath[PATH_MAX] = {};
    char fileName[PATH_MAX] = {};
    sprintf(filePath, "/proc/self/fd/%d", fileno(stream));
    if(-1 != readlink(filePath,fileName,255))
        dprintf(INFO, "write %lu bytes to %s\n",ret,fileName);
    else
        dprintf(INFO, "write %lu bytes\n",ret);

    return ret;
}

extern "C" ssize_t write(int fd, const void *buf, size_t count)
{
    using wr_t = ssize_t (*)(int,const void*,size_t);

    dprintf(DEBUG, "write message: %s\n",buf);

    auto ret = get_func_ptr<wr_t>(GLIBC_SO, "write")(fd,buf,count);

    return ret;
}

extern "C" ssize_t read(int fd, void *buf, size_t count)
{
    using rd_t = ssize_t (*)(int,const void*,size_t);

    auto ret = get_func_ptr<rd_t>(GLIBC_SO, "read")(fd,buf,count);

    dprintf(DEBUG, "read message: %s\n",buf);

    return ret;
}

extern "C" int unlink(const char *pathname)
{
    using unlink_t = int (*)(const char*);

    dprintf(INFO, "path = %s\n",pathname);

    return get_func_ptr<unlink_t>(GLIBC_SO, "unlink")(pathname);
}

extern "C" int rename(const char *old, const char *newt)
{
    using rename_t = int (*)(const char*,const char*);

    dprintf(INFO, "'%s' => '%s'\n",old,newt);

    return get_func_ptr<rename_t>(GLIBC_SO, "rename")(old,newt);
}

extern "C" int SSL_write(SSL *ssl, const void *buf, int num)
{
    using ssl_wr_t = int (*)(SSL*,const void*,int);

    dprintf(INFO, "write %s\n",buf);

    return get_func_ptr<ssl_wr_t>(OPENSSL_SO, "SSL_write")(ssl,buf,num);
}

extern "C" int SSL_read(SSL *ssl, void *buf, int num)
{
    using ssl_rd_t = int (*)(SSL*, void*,int);

    dprintf(INFO, "read %s\n",buf);

    return get_func_ptr<ssl_rd_t>(OPENSSL_SO, "SSL_read")(ssl,buf,num);
}

