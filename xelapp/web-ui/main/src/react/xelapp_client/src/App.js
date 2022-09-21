import React from 'react';
import Navbar from './controls/Navbar';
import Home from './modules/pages/Home';
import { BrowserRouter as Router, Route, Routes, Outlet } from 'react-router-dom';
import store from './store/redux-store';
import Services from './modules/pages/Services';
import Products from './modules/pages/Products';
import ContactUs from './modules/pages/ContactUs';
import SignUp from './modules/pages/SignUp';
import Marketing from './modules/pages/Marketing';
import Consulting from './modules/pages/Consulting';
import Dijkstra from './modules/algorithm/graph/impl/Dijkstra'
import { Provider } from 'react-redux';
import PrivateRoute from './controls/private_route';

function App() {
  return (
    <Router>
      <Navbar />
      <Routes>
        <Route exact path='/' element={<PrivateRoute />}>
          <Route exact path='/' element={<Home />} />
          <Route path='/dijkstra' element={<Dijkstra />} />
          <Route path='/products' element={<Products />} />
          <Route path='/contact-us' element={<ContactUs />} />
          <Route path='/marketing' element={<Marketing />} />
          <Route path='/consulting' element={<Consulting />} />
        </Route>
        <Route path='/login' element={<Provider store={store} ><SignUp /></Provider>} />
        <Route path='/register' element={<Provider store={store} ><SignUp /></Provider>} />
      </Routes>
    </Router>
  );
}

export default App;
