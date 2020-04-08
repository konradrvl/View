FROM python:alpine

RUN pip install \
mkdocs \
mkdocs-material

WORKDIR /documentation
ADD ./mkdocsFiles /documentation

EXPOSE 8000

WORKDIR /documentation/mkdocs

CMD mkdocs serve -a 0.0.0.0:8000
