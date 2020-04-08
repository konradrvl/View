FROM microsoft/aspnetcore

WORKDIR /viewserver
ADD ./buildedServer /viewserver

RUN tar -xzf view-server.1.0.0.linux-x64.tar.gz
RUN rm view-server.1.0.0.linux-x64.tar.gz

EXPOSE 4000
EXPOSE 4711

WORKDIR /viewserver/view-server.1.0.0.linux-x64

CMD ./view-server
