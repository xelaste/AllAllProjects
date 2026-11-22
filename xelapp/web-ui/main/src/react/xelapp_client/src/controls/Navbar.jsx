import { useState , useContext } from 'react';
import 'bootstrap/dist/css/bootstrap.min.css';
import { Link } from 'react-router-dom';
import Button from 'react-bootstrap/Button';
import Container from 'react-bootstrap/Container';
import Form from 'react-bootstrap/Form';
import Nav from 'react-bootstrap/Nav';
import Dropdown from 'react-bootstrap/Dropdown';
import Navbar from 'react-bootstrap/Navbar';
import NavDropdown from 'react-bootstrap/NavDropdown';
import AuthContext from '../store/auth-context';
import logoutIcon from '../images/log-out.svg';
import { useNavigate } from 'react-router-dom';

function AppNavbar() {
  const navigate = useNavigate();
  const authCtx = useContext(AuthContext);
  const [click, setClick] = useState(false);
  
  const closeMobileMenu = () => setClick(false);

  const logout = () => {
    authCtx.logout();
    navigate('/login');
  }

  return <Navbar bg="dark" variant="dark" expand="lg">
    <Container fluid>
      <Navbar.Brand href="/" className="text-decoration-none text-light">
        <span className="navbar-toggler-icon" />
      </Navbar.Brand>
      {authCtx.isLoggedIn() && (<>
      <Navbar.Toggle aria-controls="navbarScroll" />
      <Navbar.Collapse id="navbarScroll">
        <Nav
          className="me-auto my-2 my-lg-0"
          style={{ maxHeight: '100px' }}
          navbarScroll
          variant="dark"
        >
          <NavDropdown title="Games" id="navbarGames" bg="dark" menuVariant="dark">
            <NavDropdown.Item className="text-decoration-none text-light" href='/games/bullsandcows'> BullsAndCows </NavDropdown.Item>
          </NavDropdown>

          <NavDropdown title="Algorithms" id="navbarAlgorithms" menuVariant="dark">
            <Dropdown id="dropdown-item-button-graphs" variant="dark" align="end">
              <div className="dropdown-item">
                <Dropdown.Toggle as="div">Graphs</Dropdown.Toggle>
              </div>
              <div style={{ position: "relative", right: "-8em" }}>
                <Dropdown.Menu variant="dark">
                  <Dropdown.Item as="button">
                    <Link to='/dijkstra' className="text-decoration-none text-light" onClick={closeMobileMenu}>
                      Dijkstra
                    </Link>
                  </Dropdown.Item>
                  <Dropdown.Item as="button">Prim</Dropdown.Item>
                </Dropdown.Menu>
              </div>
            </Dropdown>
            <NavDropdown.Item className="text-decoration-none text-light" href='/algorithms/sorts'> 
              Sorts
            </NavDropdown.Item>
            <NavDropdown.Divider />
            <NavDropdown.Item href="#action5">Text</NavDropdown.Item>
          </NavDropdown>
          <Nav.Link href="#">
            About
          </Nav.Link>
        </Nav>
        <Form className="d-flex">
          <Form.Control
            type="search"
            placeholder="Search"
            className="me-2"
            aria-label="Search"
          />
          <Button variant="outline-success">Search</Button>
        </Form>
        <button type="button" className="me-2 btn btn-primary d-inline-flex align-items-center"  onClick={logout}>
            <img  src={logoutIcon}      alt=""   />
         </button>
      </Navbar.Collapse>
      </>)}
    </Container>
  </Navbar>
}

export default AppNavbar;
