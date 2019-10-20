var data1, data2, data3;

function refresh1() {
	const req = require('electron').remote.require;
	const { exec } = req('child_process');

	const testerProcess = exec('./tester',  (e, stdout, stderr)=> {

		if (e instanceof Error) {
			console.error(e);
			throw e;
		}
		data1 = JSON.parse(stdout);
		updateSeries();
	});
};

function refresh2() {
	const req = require('electron').remote.require;
	const { exec } = req('child_process');

	const testerProcess = exec('./tester',  (e, stdout, stderr)=> {

		if (e instanceof Error) {
			console.error(e);
			throw e;
		}
		data2 = JSON.parse(stdout);
		updateSeries();
	});
};

function refresh3() {
	const req = require('electron').remote.require;
	const { exec } = req('child_process');

	const testerProcess = exec('./tester',  (e, stdout, stderr)=> {

		if (e instanceof Error) {
			console.error(e);
			throw e;
		}
		data3 = JSON.parse(stdout);
		updateSeries();
	});
};

function clear1(){
	data1 = undefined;
	updateSeries();
}

function clear2(){
	data2 = undefined;
	updateSeries();
}

function clear3(){
	data3 = undefined;
	updateSeries();
}
function updateSeries(){
	var list = [];
	if (typeof data1 !== 'undefined'){
		list.push({name: 'series-1', data: data1.data});
	}
	if (typeof data2 !== 'undefined'){
		list.push({name: 'series-2', data: data2.data});
	}
	if (typeof data3 !== 'undefined'){
		list.push({name: 'series-3', data: data3.data});
	}
	
	chart.updateSeries(list);
}
