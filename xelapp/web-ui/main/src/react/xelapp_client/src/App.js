import React from 'react';
import Navbar from './controls/Navbar';
import Home from './modules/pages/Home';
import { BrowserRouter as Router, Route, Routes, useNavigate } from 'react-router-dom';
import store from './store/redux-store';
import Games from './modules/pages/Games';
import Products from './modules/pages/Products';
import ContactUs from './modules/pages/ContactUs';
import SignUp from './modules/pages/SignUp';
import Marketing from './modules/pages/Marketing';
import Consulting from './modules/pages/Consulting';
import Dijkstra from './modules/algorithm/graph/impl/Dijkstra'
import { Provider } from 'react-redux';
import PrivateRoute from './controls/private_route';

const SignUPComponent = () => 
{
  const navigate = useNavigate();
  return <Provider store={store} ><SignUp navigate={navigate}/></Provider>;
}
const GamesComponent = (props) => 
{
  const navigate = useNavigate();
  return <Provider store={store} ><Games name={props.name} navigate={navigate}/></Provider>;
}
function App() {
  if (process.env.NODE_ENV === "production")
  {
    console.log = function no_console() {};
  }  
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
          <Route path='/games/bullsandcows' element={<GamesComponent name="Bulls and Cows"/>} />
        </Route>
        <Route path='/login' element={<SignUPComponent/>} />
        <Route path='/register' element={<SignUPComponent/>} />
      </Routes>
    </Router>
  );
}

export default App;
