# Specifies where to get the base image (Node v12 in our case) and creates a new container for it
FROM node:12

# Set working directory. Paths will be relative this WORKDIR.
WORKDIR /usr/src/app

# Copy source files from host computer to the container
COPY . .

RUN rm -fr nodejs/node_modules/* react/coverage/* nodejs/dist/* .git .vscode
RUN rm -fr react/node_modules/* react/coverage/* nodejs/dist/* .git .vscode

WORKDIR /usr/src/app/react
RUN pwd
RUN npm config set https-proxy http://10.232.233.70:8080
RUN npm config set proxy http://10.232.233.70:8080
RUN npm install
# Build the app
RUN npm run-script docker-build
WORKDIR /usr/src/app/nodejs
RUN pwd
RUN npm install
# Specify port app runs on
EXPOSE 3000

# Run the app
CMD [ "npm", "start" ]
