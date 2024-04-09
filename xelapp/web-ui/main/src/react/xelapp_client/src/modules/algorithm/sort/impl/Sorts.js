import React, { useState, useEffect, useCallback } from "react";
import "../../../../css/App.css";
import 'bootstrap/dist/css/bootstrap.min.css';
import SortLogicalView from "../view/SortLogicalView";
import {content as defaultContent,shuffle} from '../util/ContentProvider';
import {sleep} from '../../../../util/Sleep';
export default function Sorts(props) {
    const [loaded, setLoaded] = useState(false);
    const [execution, setExecution] = useState(false);
    const [state, setState] = useState({});
    let content=defaultContent;
    async function bubbleSort()
    {
        setExecution (true);
        let complexity = 0;
        for (let i=0;i<content.length;i++)
        {
            complexity++;
            for (let j=0;j<content.length - (i+1);j++)
            {
                complexity++;
                if (content[j]>content[j+1])
                {
                    let tmp = content[j+1];
                    content[j+1] = content[j];
                    content[j] = tmp;
                    complexity+=4;
                    let newState = {
                        ...state,
                        content:content,
                        complexity:complexity
                    }
                    setState(newState);
                    await sleep(30);
                }
                else {
                    complexity++;
                }
            }
        }
        setExecution (false);
    }
    async function insertSort()
    {
        setExecution (true);
        let complexity=0;
        for (let i=1;i<content.length;i++)
        {
            complexity++;
            for (let j=i;j>0;j--)
            {
                complexity++;
                if (content[j]<content[j-1])
                {
                    let tmp = content[j-1];
                    content[j-1] = content[j];
                    content[j] = tmp;
                    complexity+=4;
                    let newState = {
                        ...state,
                        content:content,
                        complexity:complexity
                    }
                    setState(newState);
                    await sleep(30);
                }
                else {
                    complexity++
                }
            }
        }
        setExecution (false);
    }
    function onSortSelect (e) 
    { 
        let newState = {
            ...state,
            content:content,
            complexity:0,
            selectedSort:e.target.value
        }
        setState(newState);
    } 
    function isValidSort() {
      let selectedSort = state.selectedSort;
      return  selectedSort === "1" 
      ||
      selectedSort === "2"
      ||
      selectedSort === "3"
      ||
      selectedSort === "4"

    }

    function sort()
    {
        switch (state.selectedSort) { 
          case "1":
            bubbleSort();
            break;
          case "2":
            insertSort();
            break;
          case "3":
            
            break;
          case "4":
            
            break;  
        }
    }

    function sortName()
    {
        let sortName = "Please Specify";
        switch (state.selectedSort) { 
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
                                                complexity:0,
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
                                        onClick={sort}
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
                                        <label>Input size</label>
                                        <span className="m-1">{content.length}</span>
                                    </div>
                                </div>
                                <div className="row row-eq-height align-items-end">
                                    <div className="col">
                                        <label>Complexity</label>
                                        <span className="m-1">{state.complexity}</span>
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
                            <SortLogicalView title={state.selectedSort} content={content}></SortLogicalView>
                        </div>
                    </div>
                </div>
            </div>


        </div>
    </>
}