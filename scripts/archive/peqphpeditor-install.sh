curl -o peqphpeditor.zip -L https://github.com/ProjectEQ/peqphpeditor/archive/master.zip \
&& unzip peqphpeditor.zip && rm peqphpeditor.zip \
&& cp -rfv peqphpeditor-master deploy/web/html/peqphpeditor \
&& rm -rfv peqphpeditor-master \
&& cp docker/web/peqphpeditor-config.php deploy/web/html/peqphpeditor/config.php \
&& cd deploy/web/html/peqphpeditor \
&& if [ ! -e logs ]; then mkdir logs; fi \
&& find . -type d -exec chmod 0755 {} + && find . -type f -exec chmod 0644 {} + \
&& chmod 777 logs \
&& echo "Peqphpeditor installation successful." \
"Open http://[server]/peqphpeditor and log in with admin / password"
