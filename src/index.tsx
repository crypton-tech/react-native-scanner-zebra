import { useLayoutEffect } from 'react'
import {
  EventSubscription,
  NativeEventEmitter,
  NativeModules,
} from 'react-native'

const { ZebraScanner } = NativeModules
const RNZebraScanner = new NativeEventEmitter(ZebraScanner)

type EventBarcode = {
  id: string
  barcode: string
  type: string
}

type Scanner = {
  id: number
  name: string
}

type CallbackScanners = (scanners: Scanner[]) => void
type EventBarcodeHandler = (barcode: string, scannerId: string) => void
type EventHandler = (event: string, scannerId: string) => void

const supportedEvents = [
  'scanner-appeared',
  'scanner-disappeared',
  'scanner-connected',
  'scanner-disconnected',
]

const useZebraScanner = (
  onScan: EventBarcodeHandler,
  onEvent: EventHandler | undefined
) => {
  useLayoutEffect(() => {
    const handleEvent = (data: EventBarcode) => {
      console.log('Event: Barcode', data)
      if (onScan) {
        onScan(data.barcode || '', data.id)
      }
    }

    const listeners: EventSubscription[] = []
    listeners.push(RNZebraScanner.addListener('scanner-barcode', handleEvent))

    if (onEvent) {
      supportedEvents.forEach((event: string) => {
        listeners.push(
          RNZebraScanner.addListener(event, (data) => {
            console.log('Event:', event, data)
            onEvent(event, data.id || '')
          })
        )
      })
    }

    return () => {
      listeners.forEach((listener) => {
        listener.remove()
      })
    }
  })

  const setEnabled = (isEnabled: boolean) => {
    NativeModules.ZebraScanner.setEnabled(isEnabled)
  }

  const getActiveScanners = (callback: CallbackScanners) => {
    NativeModules.ZebraScanner.getActiveScanners((scanners: Scanner[]) => {
      callback(scanners)
    })
  }

  return {
    setEnabled,
    getActiveScanners,
  }
}

export default useZebraScanner
