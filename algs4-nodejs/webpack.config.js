const path = require('path');
const webpack = require('webpack');
const MiniCssExtractPlugin = require('mini-css-extract-plugin');
const { CleanWebpackPlugin } = require('clean-webpack-plugin');

const devMode = process.argv.indexOf('-p')===-1;
const nodeEnv = devMode ? 'development' : 'production';
console.log("####################")
console.log(process.argv.indexOf('-p'));
console.log(devMode)
console.log(nodeEnv)
console.log("###################")

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
    path: path.resolve(__dirname, '../nodejs/dist'),
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
    new CleanWebpackPlugin(),
    new MiniCssExtractPlugin({
      // Options similar to the same options in webpackOptions.output
      // both options are optional
      //filename: devMode ? '[name].css' : '[name].[hash].css',
      //chunkFilename: devMode ? '[name][id].css' : '[id].[hash].css',      
      filename: '[name]-bundle.css',
      //chunkFilename: '[id].css',
    })
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
        use: [
          {
            loader: MiniCssExtractPlugin.loader,
            options: {
              publicPath: path.resolve(__dirname, '../nodejs/dist'),
              //path.join(__dirname, '/dist')
            },
          },
          'css-loader'
        ]
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
        apiUrl: devMode ? 'http://localhost:3000' : 'https://bullandcow.herokuapp.com'
    })
}
};
module.exports = (env, argv) =>  conf

