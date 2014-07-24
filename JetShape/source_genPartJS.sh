

#g++ -m64 -Wall -I$ROOTSYS/include -L$ROOTSYS/lib -lTree -ldl -lPhysics -lGpad -lHtml -lMinuit class_def/JetAna.C my_test.C -o my_test.out
#/usr/bin/g++ -m64 -Wall -I$ROOTSYS/include -L$ROOTSYS/lib -lHist -lMatrix -lGraf -lCore -lTree -ldl -lPhysics -lGpad -lHtml -lMinuit class_def/JetAna.C my_test.C -o my_test.out
#/usr/bin/g++ -m64 -Wall -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --libs --glibs` class_def/JetIDAna_IC5.C class_def/JetIDAna.C JetIDAna_test.C -o JetIDAna_test.out
#g++ -Wall -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --libs --glibs` class_def/skim.C class_def/Evt.C class_def/HLT.C class_def/track.C class_def/akPu3PFJet.C class_def/pfTree.C JetShape.C -o pfjet.out
g++ -Wall -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --libs --glibs` class_def/skim.C class_def/Evt.C class_def/HLT.C class_def/track.C class_def/akPu3PFJet.C class_def/pfTree.C class_def/GenParticle.C genParticleJS.C -o genPartJS.out
