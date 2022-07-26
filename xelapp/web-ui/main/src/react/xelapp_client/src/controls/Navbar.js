import React, { useState } from 'react';
import 'bootstrap/dist/css/bootstrap.min.css';
import { Link } from 'react-router-dom';
import Button from 'react-bootstrap/Button';
import Container from 'react-bootstrap/Container';
import Form from 'react-bootstrap/Form';
import Nav from 'react-bootstrap/Nav';
import DropdownButton from 'react-bootstrap/DropdownButton';
import Dropdown from 'react-bootstrap/Dropdown';
import Navbar from 'react-bootstrap/Navbar';
import NavDropdown from 'react-bootstrap/NavDropdown';

function AppNavbar() {
  const [click, setClick] = useState(false);
  const [dropdown, setDropdown] = useState(false);

  const handleClick = () => setClick(!click);
  const closeMobileMenu = () => setClick(false);

  const onMouseEnter = () => {
    if (window.innerWidth < 960) {
      setDropdown(false);
    } else {
      setDropdown(true);
    }
  };

  const onMouseLeave = () => {
    if (window.innerWidth < 960) {
      setDropdown(false);
    } else {
      setDropdown(false);
    }
  };

  return <Navbar bg="dark" variant="dark" expand="lg">
    <Container fluid>
      <Navbar.Brand href="#"><span class="navbar-toggler-icon" /></Navbar.Brand>
      <Navbar.Toggle aria-controls="navbarScroll" />
      <Navbar.Collapse id="navbarScroll">
        <Nav
          className="me-auto my-2 my-lg-0"
          style={{ maxHeight: '100px' }}
          navbarScroll
          variant="dark"
        >
          <NavDropdown title="Games" id="navbarGames" bg="dark" variant="dark">
            <NavDropdown.Item href="#action3">BullsAndCows</NavDropdown.Item>
          </NavDropdown>

          <NavDropdown title="Algorithms" id="navbarAlgorithms" menuVariant="dark">
            <Dropdown id="dropdown-item-button-graphs" variant="dark" align="end">
              <div class="dropdown-item">
                <Dropdown.Toggle as="div">Graphs</Dropdown.Toggle>
              </div>
              <div style={{ position: "relative",right: "-8em"}}>
              <Dropdown.Menu variant="dark">
                <Dropdown.Item as="button">Dijkstra</Dropdown.Item>
                <Dropdown.Item as="button">Prim</Dropdown.Item>
              </Dropdown.Menu>
              </div>
            </Dropdown>
            <NavDropdown.Item href="#action4">Sorts</NavDropdown.Item>
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
      </Navbar.Collapse>
    </Container>
  </Navbar>
}

export default AppNavbar;
