import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'
import fs from 'fs';
import path from 'path';
import pkg from './package.json';


export default defineConfig({
  root: './src',
  build: {
    // Direct the build output outside the src directory to your standard dist folder
    outDir: '../dist',
    emptyOutDir: true,
  }
});
