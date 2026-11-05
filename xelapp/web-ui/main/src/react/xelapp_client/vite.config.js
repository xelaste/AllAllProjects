import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'
import fs from 'fs';
import path from 'path';
import pkg from './package.json' with { type: 'json' };


export default defineConfig({
  root: './src',
  envDir: '..',
  build: {
    // Direct the build output outside the src directory to your standard dist folder
    outDir: '../dist',
    emptyOutDir: true,
  }
});
