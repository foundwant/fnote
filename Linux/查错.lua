--[[
    Nginx��������: error while loading shared libraries: libpcre.so.1
    # /usr/local/nginx/sbin/nginx
        "/usr/local/nginx/sbin/nginx: 
        error while loading shared libraries: libpcre.so.1: cannot open shared object file: No such file or directory"
    �Ӵ�����ʾ��Ϣ���Ե�֪����Ϊȱ��lib�ļ����£���һ���鿴�������ݣ�
    # ldd $(which /usr/local/nginx/sbin/nginx)
        libpthread.so.0 => /lib64/libpthread.so.0 (0x00000030e8400000)
        libcrypt.so.1 => /lib64/libcrypt.so.1 (0x00000030f9a00000)
        libpcre.so.1 => not found
        libcrypto.so.6 => /lib64/libcrypto.so.6 (0x00000030f2a00000)
        libz.so.1 => /lib64/libz.so.1 (0x00000030e8800000)
        libc.so.6 => /lib64/libc.so.6 (0x00000030e7800000)
        /lib64/ld-linux-x86-64.so.2 (0x00000030e7400000)
        libdl.so.2 => /lib64/libdl.so.2 (0x00000030e8000000)

    �鿴�����ʾ �� libpcre.so.1 => not found ��ͬʱע��lib���·������/lib/* �� /lib64/* ֮��

    ����취��
    --�鿴lib��
    #ls /lib64/ |grep pcre
    libpcre.so.0
    libpcre.so.0.0.1

    --���������
    #ln -s /lib64/libpcre.so.0.0.1 /lib64/libpcre.so.1
    ps: Ҳ�п��� pcre lib�ļ���Ŀ¼��/usr/local/lib64/
]]