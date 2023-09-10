/* 
THIS IS THE CODE YOU SHOULD USE FOR YOUR 
NGINX CONFIGURATION called "nginx.conf". 
Download nginx and navigate to 
'C:/nginx/conf/nginx.conf' after download.

With this, you should have nginx server 
running on the browser on:
        
        localhost:8080

------------------------- copy from here -------

#user  nobody;
worker_processes  1;

events {
    worker_connections  1024;
}

http {
    include       mime.types;
    default_type  application/octet-stream;

    sendfile        on;

    #keepalive_timeout  0;
    keepalive_timeout  65;


    server {
        listen       8080;
        server_name  localhost;

        location / {
            # root   "C:/nginx/htmldocs/website/shopping/";
            # index  index.html index.htm app.html website.html;
            proxy_pass http://localhost:8081;
            proxy_set_header Host $host;
            proxy_set_header X-Real-IP $remote_addr;
            proxy_set_header X_Forwarded_For $proxy_add_x_forwarded_for;
        }

        error_page   500 502 503 504  /50x.html;
        location = /50x.html {
            root   html;
        }
    }
}

--------------------- stop copying here ----------
*/