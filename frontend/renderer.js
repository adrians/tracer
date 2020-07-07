var data = [];

function refresh(i) {
	const req = require('electron').remote.require;
	const { exec } = req('child_process');

	const testerProcess = exec('./tester',  (e, stdout, stderr)=> {
		if (e instanceof Error) {
			console.error(e);
			throw e;
		}
		data[i] = JSON.parse(stdout);
		updateSeries();
	});
};

function clearSeries(i){
	data[i] = undefined;
	updateSeries();
}

function updateSeries(){
	var list = [];
	if (typeof data[1] !== 'undefined'){
		list.push({name: 'series-1', data: data[1].data});
	}
	if (typeof data[2] !== 'undefined'){
		list.push({name: 'series-2', data: data[2].data});
	}
	if (typeof data[3] !== 'undefined'){
		list.push({name: 'series-3', data: data[3].data});
	}
	
	chart.updateSeries(list);
	document.getElementById("dump").value = JSON.stringify(data, null, 2);
}
