import React from 'react';
import Navbar from './controls/Navbar';
import Home from './components/pages/Home';
import { BrowserRouter as Router,Route, Routes } from 'react-router-dom';
import Services from './components/pages/Services';
import Products from './components/pages/Products';
import ContactUs from './components/pages/ContactUs';
import SignUp from './components/pages/SignUp';
import Marketing from './components/pages/Marketing';
import Consulting from './components/pages/Consulting';
import Dijkstra from './components/algorithm/Dijkstra'

function App() {
  return (
    <Router>
      <Navbar />
      <Routes>
        <Route path='/' exact element={<Home/>} />
        <Route path='/dijkstra' element={<Dijkstra/>} />
        <Route path='/products' element={<Products/>} />
        <Route path='/contact-us' element={<ContactUs/>} />
        <Route path='/sign-up' element={<SignUp/>} />
        <Route path='/marketing' element={<Marketing/>} />
        <Route path='/consulting' element={<Consulting/>} />
      </Routes>
    </Router>
  );
}

export default App;
