import React, { useState, useCallback, useEffect } from 'react'
import {
  SafeAreaView,
  ScrollView,
  StyleSheet,
  View,
  Text,
  TouchableOpacity
} from 'react-native'
import useZebraScanner from 'react-native-scanner-zebra'

interface IEventBarcode {
  code: string
  scannerId: number
}

interface IEvent {
  name: string
  scannerId: number
}

interface IEventState {
  barcode: IEventBarcode | null
  events: IEvent[]
}

const styles = StyleSheet.create({
  wrapper: {
    width: '100%',
    height: '100%',
  },
  container: {
    flex: 1,
    flexDirection: 'column',
    alignItems: 'stretch',
    paddingTop: 20,
    paddingRight: 20,
    paddingLeft: 20,
    paddingBottom: 20,
    width: '100%',
    height: '100%',
  },
  title: {
    height: 30,
    fontSize: 20,
    fontWeight: 'bold',
    textAlign: 'center',
    margin: 10,
    color: '#202020'
  },
  headingRow: {
    width: '100%',
    height: 30,
  },
  heading: {
    fontSize: 18,
    fontWeight: 'bold',
    textAlign: 'left',
    color: '#202020'
  },
  event: {
    width: '100%',
    flexDirection: 'row',
    alignItems: 'center',
    height: 40,
  },
  eventRow: {
    borderBottomWidth: 1,
    borderBottomColor: '#ddd',
    paddingRight: 10,
    paddingLeft: 10,
  },
  eventName: {
    width: '49%',
    fontSize: 16,
    textAlign: 'left',
  },
  eventData: {
    width: '49%',
    fontSize: 16,
    textAlign: 'left',
  },
  eventList: {
    flexGrow: 1,
    width: '100%',
  },
  eventListContent: {
    flex: 1,
    flexDirection: 'column',
  },
  actions: {
    paddingTop: 10,
    width: '100%',
    flexDirection: 'row',
    height: 60,
    justifyContent: 'flex-start',
  },
  button: {
    justifyContent: 'center',
    borderRadius: 5,
    borderColor: '#ddd',
    borderWidth: 1,
    height: 40,
    paddingRight: 10,
    paddingLeft: 10,
    width: 180,
    marginRight: 10,
  },
  buttonLabel: {
    fontSize: 18,
    textAlign: 'center',
  }
});

const App = () => {
  const [state, setState] = useState<IEventState>({
    barcode: null,
    events: [],
  });

  const onScan = useCallback((code, scannerId) => {
    setState((prevState) => {
      return { ...prevState, barcode: { code, scannerId } };
    });
  }, [setState])

  const onEvent = useCallback((name, scannerId) => {
    setState((prevState) => {
      prevState.events.unshift({ name, scannerId });
      return { ...prevState };
    });
  }, [setState]);

  const { setEnabled, getActiveScanners } = useZebraScanner(onScan, onEvent)

  const onEnable = useCallback(() => {
    setEnabled(true)
  }, [setEnabled])

  const onDisable = useCallback(() => {
    setEnabled(false)
  }, [setEnabled])

  useEffect(() => {
    getActiveScanners((scanners) => {
      console.log('Active scanners', scanners);
    })
  }, [])

  return (
    <SafeAreaView style={styles.wrapper}>
      <View style={styles.container}>
        <Text style={styles.title}>Zebra Scanner Demo</Text>
        <View style={styles.headingRow}><Text style={styles.heading}>Actions:</Text></View>
        <View style={styles.actions}>
            <TouchableOpacity onPress={onEnable}>
              <View style={styles.button}>
                <Text style={styles.buttonLabel}>Enable Scanners</Text>
              </View>
            </TouchableOpacity>
            <TouchableOpacity onPress={onDisable}>
              <View style={styles.button}>
                <Text style={styles.buttonLabel}>Disable Scanners</Text>
              </View>
            </TouchableOpacity>
        </View>
        <View style={styles.headingRow}><Text style={styles.heading}>Barcode:</Text></View>
        {state.barcode !== null && (
          <View style={styles.event}>
            <Text style={styles.eventName}>Code: {state.barcode.code}</Text>
            <Text style={styles.eventData}>Scanner: {`${state.barcode.scannerId}`}</Text>
          </View>
        )}
        <View style={styles.headingRow}><Text style={styles.heading}>Events:</Text></View>
        <ScrollView style={styles.eventList} contentContainerStyle={styles.eventListContent}>
          {state.events.map((event) => (
            <View style={[styles.event, styles.eventRow]}>
              <Text style={styles.eventName}>Event: {event.name}</Text>
              <Text style={styles.eventData}>Scanner: {`${event.scannerId}`}</Text>
            </View>
          ))}
        </ScrollView>
      </View>
    </SafeAreaView>
  );
}

export default App
