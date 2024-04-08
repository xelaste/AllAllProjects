import React,{ useState, useEffect, useCallback } from "react";
import "../../../../css/App.css";
import 'bootstrap/dist/css/bootstrap.min.css';
import SortLogicalView from "../view/SortLogicalView";
export default function Sorts(props) {
    const [loaded, setLoaded] = useState(false);
    useEffect(() => {
        if (!loaded)
        {
            setLoaded(true);
        }
      }, []);
    return <>
        <div className="home">
            <div className="container-fluid p-20">
                <div className="row text-center">
                    <h3 className="display-4 text-primary">Sorts</h3>
                </div>
                <div className="row h-100">
                    <div className="col-3 display-4 text-primary">Content</div>
                    <div className="col-9">
                        <div className="fs-2 text-secondary">xxx</div>
                        <div
                            id="algorithmContainer"
                            style={{ width: "100%", height: "80%"  }}
                            class="overflow-auto"
                        >
                            <SortLogicalView title="yyys"></SortLogicalView>
                        </div>
                    </div>
                </div>
            </div>


        </div>
    </>
}