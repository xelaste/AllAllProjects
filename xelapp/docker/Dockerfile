FROM node:20.11.1 as builder

RUN npm install -g npm@latest

# Paths will be relative this WORKDIR.
WORKDIR /usr/src/app

# Copy source files from host computer to the container
COPY web-ui ./web-ui
COPY backend ./backend

WORKDIR web-ui/main/src/react/xelapp_client
RUN pwd
RUN npm --maxsockets 1 install
# Build the app
RUN npm run build
WORKDIR /usr/src/app/web-ui/main/src/react/xelapp_client
RUN cp -R build /usr/src/app/backend/main/src/nodejs
WORKDIR /usr/src/app/backend/main/src/nodejs
RUN mv build dist

FROM node:20.11.1
COPY --from=builder ./usr/src/app/backend/main/src/nodejs/ ./usr/app/nodejs/
COPY --from=builder ./usr/src/app/backend/main/src/resources/ ./usr/app/resources/
WORKDIR /usr/app/nodejs
RUN npm --maxsockets 1 install
# Specify port app runs on
EXPOSE 3030
# Run the app
CMD [ "npm", "start" ]




