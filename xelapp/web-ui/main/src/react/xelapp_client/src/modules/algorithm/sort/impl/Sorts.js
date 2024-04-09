import React, { useState, useEffect, useCallback } from "react";
import "../../../../css/App.css";
import 'bootstrap/dist/css/bootstrap.min.css';
import SortLogicalView from "../view/SortLogicalView";
import {content as defaultContent,shuffle} from '../util/ContentProvider';
export default function Sorts(props) {
    const [loaded, setLoaded] = useState(false);
    const [execution, setExecution] = useState(false);
    const [selectedSort,setSelectedSort] = useState("Please Specify");
    const [state, setState] = useState({});
    let content=defaultContent;
    function onSortSelect (e) 
    { 
        setSelectedSort (e.target.value)
    } 
    function isValidSort() {
      return  selectedSort === "1" 
      ||
      selectedSort === "2"
      ||
      selectedSort === "3"
      ||
      selectedSort === "4"

    }
    function sortName()
    {
        let sortName = "Please Specify";
        switch (selectedSort) { 
          case "1":
            sortName = "Bubble Sort"
            break;
          case "2":
            sortName = "Insertion Sort"
            break;
          case "3":
            sortName = "Merge Sort";
            break;
          case "4":
            sortName = "Quick Sort";
            break;  
        }
        return sortName;
    }
    useEffect(() => {
        if (!loaded) {
            setLoaded(true);
        }
    }, []);
    return <>
        <div className="home">
            <div className="container-fluid">
                <div className="row text-center">
                    <h3 className="display-4 text-primary">Sorts</h3>
                </div>
                <div className="row h-100">
                    <div className="col-3 display-6 text-primary">
                        <div className="card fs-6 mt-10 p-6 w-100 border-dark bg-secondary mb-3">
                            <div className="card-header  bg-dark">
                                <h3 className="text-white">Configuration</h3>
                            </div>
                            <div className="card-body">
                                <form>
                                    <label className="mb-1" htmlFor="sortTypesList">Sorting algorithms</label>
                                    <select disabled={execution} id="sortTypesList" onChange={onSortSelect} className="form-select form-label form-select-lg mb-3">
                                        <option value="Please Specify" selected>Select Sort Algorithm</option>
                                        <option value="1">Bubble Sort</option>
                                        <option value="2">Insert Sort</option>
                                        <option value="3">Merge Sort</option>
                                        <option value="4">Quick Sort</option>
                                    </select>


                                    <button
                                        type="button"
                                        disabled={execution}
                                        style={{ width: "6em" }}
                                        onClick={(e)=>{
                                            shuffle(content);
                                            let newState = {
                                                ...state,
                                                content:content
                                            }
                                            setState(newState);
                                        }}
                                        className="btn btn-primary mt-2"
                                    >
                                        Shuffle
                                    </button>
                                    <button
                                        type="button"
                                        disabled={execution || !isValidSort()}
                                        style={{ width: "6em" }}


                                        className="btn btn-primary mt-2 mx-2"
                                    >
                                        Run
                                    </button>
                                </form>
                            </div>
                        </div>
                        <div style={{ height: "38%" }} className="card fs-6  w-100 border-dark bg-info mb-3 overflow-auto">
                            <div className="card-header bg-primary">
                                {execution ? (
                                    <h3 className="bg-secondary blinking">Running</h3>
                                ) : (
                                    <h3 className="text-dark">Results</h3>
                                )}
                            </div>
                            <div className="card-body text-dark overflow-auto">
                                <div className="row row-eq-height align-items-end">
                                    <div className="col">
                                        <label>Complexity</label>
                                        <span className="m-1">0</span>
                                    </div>
                                </div>

                            </div>
                        </div>

                    </div>
                    <div className="col-9">
                        <div className="ps-2 me-1 fs-5 bg-secondary text-info">{sortName()}</div>
                        <div
                            id="algorithmContainer"
                            style={{ width: "100%", height: "80%" }}
                            class="overflow-auto"
                        >
                            <SortLogicalView title={selectedSort} content={content}></SortLogicalView>
                        </div>
                    </div>
                </div>
            </div>


        </div>
    </>
}