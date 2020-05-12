const path = require('path');
const webpack = require('webpack');
var ExtractTextPlugin = require('extract-text-webpack-plugin');

const devBuild = process.env.NODE_ENV !== 'production';
const nodeEnv = devBuild ? 'development' : 'production';
const apiUrl = 'production' == process.env.NODE_ENV ? 'https://bullandcow.herokuapp.com' :  'http://localhost:3000';

let conf = {
  mode:nodeEnv,
  context: path.resolve(__dirname, 'src'), // `__dirname` is root of project and `src` is source
  devtool:'inline-source-map',
  entry: {
    app: [
      './main.jsx',
    ],
    vendor: [
      'react',
      'react-dom',
    ],
  },
  output: {
    filename: '[name]-bundle.js',
    path: path.join(__dirname, '/dist'),
    publicPath: '/'
  },
  resolve: {
    extensions: ['.js', '.jsx'],
  },
  optimization: {
    runtimeChunk: "single", // enable "runtime" chunk
    splitChunks: {
      cacheGroups: {
        vendor: {
          test: /[\\/]node_modules[\\/]/,
          name: "vendor",
          chunks: "all"
        }
      }
    }
  },
  plugins: [
    new webpack.DefinePlugin({
      'process.env': {
        NODE_ENV: JSON.stringify(nodeEnv),
      },
    }),
    
    new ExtractTextPlugin('styles.css')
  ],
  module: {
    rules: [
      {
        test: /\.js$/,
        exclude: /(spec|node_modules|bower_components)/,
        loader: 'babel-loader', // 'babel-loader' is also a legal name to reference
        options: {
          babelrc: false,
          presets: ['es2015'],
          plugins: ["transform-class-properties","transform-object-rest-spread"]
        }
      },
      {
        test:/\.css$/,
        use:['style-loader','css-loader']
      },
      {
        test: /.jsx?$/,
        exclude: /node_modules/,
        include: path.join(__dirname, 'src'),
        use: [
          {
            loader: 'babel-loader',
            options: {
              babelrc: false,
              plugins: ["transform-class-properties","transform-object-rest-spread"],
              presets: [
                ['es2015', { modules: false }],
                'react',
              ],
            }
          }
        ]
      },
    ]
  },
  devServer: {
    contentBase: [path.join(__dirname, 'public'), path.join(__dirname, 'dist')],
    compress: true,
    hot: true,
    port: 9001
  },
  externals: {
    // global app config object
    config: JSON.stringify({
        apiUrl: apiUrl 
    })
}
};
module.exports = (env, argv) => conf;
