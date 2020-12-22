import React, { useState, useCallback } from 'react'
import { StyleSheet, View, Text } from 'react-native'
import useZebraScanner from 'react-native-scanner-zebra'

const styles = StyleSheet.create({
	container: {
		flex: 1,
		justifyContent: 'center',
		alignItems: 'center',
		backgroundColor: '#F5FCFF',
	},
	heading: {
		fontSize: 20,
		textAlign: 'center',
		margin: 10,
	},
	event: {
		paddingTop: 20,
		width: '100%',
	},
	eventName: {
		fontSize: 16,
		fontWeight: 'bold',
		textAlign: 'left',
		width: '100%',
	},
	eventData: {
		paddingTop: 10,
		fontSize: 16,
		textAlign: 'left',
		width: '100%',
	},
});

const App = () => {
	const [state, setState] = useState({
		isAvailable: false,
		barcode: '',
		scannerId: '',
	});

	const onScan = useCallback((barcode, scannerId) => {
		setState({
			isAvailable: true,
			barcode,
			scannerId
		})
	}, [setState])

	useZebraScanner(onScan)

	return (
		<View style={styles.container}>
			<Text style={styles.heading}>ZebraScanner Demo</Text>
			{state.isAvailable && (
				<View style={styles.event}>
					<Text style={styles.eventName}>Barcode: {state.barcode}</Text>
					<Text style={styles.eventData}>Scanner: {state.scannerId}</Text>
				</View>
			)}
		</View>
	);
}

export default App
