import unittest
from EventStore import EventStore
import os

class EventStoreTestCase(unittest.TestCase):

    def setUp(self):
        self.filename = 'example.root'
        self.assertTrue( os.path.isfile(self.filename) )
        self.store = EventStore(self.filename)
        
    def test_eventloop(self):
        self.assertTrue( self.store.getEntries() >= 0 )
        self.assertEqual( self.store.getEntries(), len(self.store) )
        for iev, event in enumerate(self.store):
            self.assertTrue( True )

    def test_read_particles(self):
        for iev, event in enumerate(self.store):
            print iev
            genptcs = event.get('GenParticle')
            self.assertTrue(len(genptcs)>0.)
            for ptc in genptcs:
                self.assertTrue(ptc.Core().P4.Pz!=0.)
            
    def test_direct_navigation(self):
        event0 = self.store[0]
        # event is of the store class
        self.assertEqual( event0.__class__, self.store.__class__)

    def test_collections(self):
        '''test that an existing collection can be read, 
        and that a non existing collection gives None.'''
        evinfo = self.store.get("EventInfo")
        self.assertTrue( len(evinfo)>0 )
        particles = self.store.get("CollectionNotThere")
        self.assertFalse(particles is None)


    # def test_handles(self):
    #     assocs = self.store.get("GenJetParticle")
    #     particles = self.store.get("GenParticle")
    #     jets = self.store.get("GenJet")
    #     self.assertTrue( len(assocs)>0 )
    #     jet = assocs[0].Jet()
    #     ptc = assocs[0].Particle()
    #     self.assertIsNotNone( jet )
    #     self.assertIsNotNone( ptc )
    #     self.assertTrue( jet in jets )
    #     self.assertTrue( ptc in particles )
    #     self.assertFalse( jet in particles )
    #     self.assertFalse( ptc in jets )
    #     ptcsInJet0 = []
    #     for assoc in assocs:
    #         jet = assoc.Jet()
    #         if jet == jets[0]:
    #             ptcsInJet0.append( assoc.Particle() )
    #     self.assertTrue( len(ptcsInJet0) > 0)
                
            

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

