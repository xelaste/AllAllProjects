// Karma configuration
// Generated on Wed Aug 10 2016 22:07:33 GMT+0300 (IDT)
const path = require('path');

var webpackConfig = {
  module: {
    rules: [
        {
            enforce: 'pre',
            test: /\.js$/,
            use: ['source-map-loader'],
            exclude: [
                /node_modules/,
                /spec/
            ]
        },
        {
          test: /\.js$/,
          exclude: /(spec|node_modules|bower_components)/,
          loader: 'babel-loader', // 'babel-loader' is also a legal name to reference
          options: {
            babelrc: false,
            presets: ['es2015'],
            plugins: ["transform-class-properties"]
          }
        },
      
        {
            enforce: 'post',
            test: /\.(js|ts)$/,
            loader: 'istanbul-instrumenter-loader',
            options: { esModules: true },
            exclude: [
                /node_modules/,
                /spec/
            ]
        },
        
        { test: /\.html$/, loader: 'html-loader' }
    ]
},
externals: {
  // global app config object
  config: JSON.stringify({
      apiUrl: 'http://localhost:3000'
  })
}
};
webpackConfig.devtool = 'inline-source-map';
webpackConfig.mode="development";

module.exports = function(config) {
  config.set({

    // base path that will be used to resolve all patterns (eg. files, exclude)
    basePath: '',


    // frameworks to use
    // available frameworks: https://npmjs.org/browse/keyword/karma-adapter
    frameworks: ['jasmine'],


    // list of files / patterns to load in the browser
    files: [
      'spec/tests.bundle.js',
       ],

    // list of files to exclude
    exclude: [
      '**/*.swp'
    ],


    // preprocess matching files before serving them to the browser
    // available preprocessors: https://npmjs.org/browse/keyword/karma-preprocessor
    preprocessors: {
      'spec/tests.bundle.js': ['webpack'],
    },

    webpack: webpackConfig,
    webpackMiddleware: {
      noInfo: true,
    },

    // test results reporter to use
    // possible values: 'dots', 'progress'
    // available reporters: https://npmjs.org/browse/keyword/karma-reporter
   // reporters: ['mocha','progress', 'kjhtml', 'coverage'],
   reporters: ['mocha', 'progress', 'coverage-istanbul' ],
  coverageIstanbulReporter: {
    reports: [ 'html','text-summary' ],
    fixWebpackSourcePaths: true,
    combineBrowserReports: true,
    dir: path.join(__dirname, 'coverage'),
    verbose: false,
    // Omit files with no statements, no functions and no branches from the report
    skipFilesWithNoCoverage: true
  },


    // web server port
    port: 9876,


    // enable / disable colors in the output (reporters and logs)
    colors: true,


    // level of logging
    // possible values: config.LOG_DISABLE || config.LOG_ERROR || config.LOG_WARN || config.LOG_INFO || config.LOG_DEBUG
    logLevel: config.LOG_INFO,


    // enable / disable watching file and executing tests whenever any file changes
    autoWatch: true,


    // start these browsers
    // available browser launchers: https://npmjs.org/browse/keyword/karma-launcher
   // browsers: ['Chrome'],
    //chromeOptions: {
    //  args: [ "--headless", "--disable-gpu", "--window-size=800x600" ]
    //},
    

    // Continuous Integration mode
    // if true, Karma captures browsers, runs the tests and exits
    singleRun: false,
    
    //
    //browsers: ['Chrome'],
    
    browsers: ['ChromeHeadless'],
    customLaunchers: {
      ChromeHeadless: {
        base: 'Chrome',
        flags: [
          // See https://chromium.googlesource.com/chromium/src/+/lkgr/headless/README.md
          '--headless',
          '--disable-gpu',
          // Without a remote debugging port, Google Chrome exits immediately.
          '--remote-debugging-port=9222',
        ],
      }
    },
    
    // Concurrency level
    // how many browser should be started simultaneous
    concurrency: Infinity,
  })
}
