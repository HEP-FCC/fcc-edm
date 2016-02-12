import unittest
from EventStore import EventStore
import os
from datetime import datetime

class EventStoreTestCase(unittest.TestCase):
    '''Test the python event store interface.'''
    
    def setUp(self):
        self.filename = 'example.root'
        self.assertTrue( os.path.isfile(self.filename) )
        self.store = EventStore(self.filename)
        
    def test_eventloop(self):
        '''Test that 
        - the store contains events, 
        - the length of the store is the number of entries, 
        - one can loop on the events.
        '''
        self.assertTrue( self.store.getEntries() >= 0 )
        self.assertEqual( self.store.getEntries(), len(self.store) )
        for iev, event in enumerate(self.store):
            self.assertTrue( True )

    def test_read_particles(self):
        '''Test that
        - the GenParticle objects can be used 
        - the processing is faster than 100 Hz. 
        '''
        start = datetime.now()
        for iev, event in enumerate(self.store):
            genptcs = event.get('GenParticle')
            self.assertTrue(len(genptcs)>0.)
            for ptc in genptcs:
                self.assertTrue(ptc.Core().P4.Pz!=0.)
        stop = datetime.now()
        time_per_event = float( (stop - start).seconds )/ len(self.store) 
        self.assertLess(time_per_event, 1e-2) # 3e-4 on Colin's mac  
                
    def test_direct_navigation(self):
        '''Test that 
        - one can move to a given event
        '''
        event0 = self.store[0]
        # event is of the store class
        self.assertEqual( event0.__class__, self.store.__class__)

    def test_collections(self):
        '''test that an existing collection can be read, 
        and that a non existing collection gives None.
        '''
        evinfo = self.store.get("EventInfo")
        self.assertTrue( len(evinfo)>0 )
        particles = self.store.get("CollectionNotThere")
        self.assertFalse(particles is None)

    # COLIN should add more tests of the event data model,
    # like associations, etc

if __name__ == "__main__":
    from ROOT import gSystem
    from subprocess import call
    import os 
    gSystem.Load("libdatamodelDict")
    # creating example file for the tests
    if not os.path.isfile('example.root'):
        write = '{fccedm}/bin/fccedm-write'.format(fccedm=os.environ['FCCEDM'])
        print write 
        call(write)
    unittest.main()

