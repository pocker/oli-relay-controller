const path = require("path");
const HtmlWebpackPlugin = require("html-webpack-plugin");
const TerserPlugin = require("terser-webpack-plugin");

module.exports = {
  entry: path.join(__dirname, "src", "index.js"),
  output: {
    path: path.resolve(__dirname, "dist"),
  },
  devServer: {
    proxy: {
      "/status": "http://192.168.0.61",
      "/config": "http://192.168.0.61",
      "/restart": "http://192.168.0.61",
      "/update": "http://192.168.0.61",
    },
  },
  module: {
    rules: [
      {
        test: /\.?js$/,
        exclude: /node_modules/,
        use: {
          loader: "babel-loader",
          options: {
            presets: ["@babel/preset-env", "@babel/preset-react"],
          },
        },
      },
    ],
  },
  optimization: {
    minimizer: [
      new TerserPlugin({
        extractComments: false,
      }),
    ],
  },
  performance: {
    maxEntrypointSize: 1024000,
    maxAssetSize: 1024000,
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: path.join(__dirname, "public", "index.html"),
    }),
  ],
};
