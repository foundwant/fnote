FROM centos as builder

#build 一条命令对应一个缓存层;
#build 的时候按照dockerfile里面的命令一条一条顺序执行,
#如果命令不变以及涉及到的文件也无改动,就可能会用到缓存;
#如果某一层缓存失效,会导致下面所有层的缓存都失效;
#Dockerfile 中每一个指令都会创建一个镜像层,上层是依赖于下层的,
#无论什么时候,只要某一层发生变化,其上面所有层的缓存都会失效;

WORKDIR /usr/local/src

COPY lua-uuid   /usr/local/src/lua-uuid
COPY lua-rsa    /usr/local/src/lua-rsa
COPY pre-ngx.sh /usr/local/src/
ADD  RPM-GPG-KEY-EPEL-7 /etc/pki/rpm-gpg

RUN    rpm --import /etc/pki/rpm-gpg/RPM-GPG-KEY-EPEL* \
    && rpm --import /etc/pki/rpm-gpg/RPM-GPG-KEY-CentOS* \
    && sh pre-ngx.sh

COPY ngx.sh /usr/local/src/nginx-1.12.2
WORKDIR     /usr/local/src/nginx-1.12.2
RUN sh ngx.sh
COPY lualib /usr/local/nginx/lua/lib/lua/5.1
COPY conf   /usr/local/nginx/conf


FROM centos
COPY --from=builder /etc/ld.so.conf /etc/ld.so.conf
COPY --from=builder /usr/local /usr/local/
RUN ldconfig

ENV PATH /usr/local/nginx/sbin:/usr/local/sbin:/usr/local/bin:$PATH
WORKDIR  /usr/local/nginx

##仅仅是声明暴露哪些端口,并没有实际作用
##通过-p参数来指定
EXPOSE 80 8080

##ENTRYPOINT和CMD联合使用时,CMD语义退变,不会直接被运行,会变成ENTRYPOINT的参数
ENTRYPOINT ["nginx"]
CMD ["-g","daemon off;"]

# "daemon on;"如果容器内的进程在后台运行那么容器将不会运行
# CMD /bin/sh -c 'nginx -g "daemon off;"'