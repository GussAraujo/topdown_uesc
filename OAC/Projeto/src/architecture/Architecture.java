package architecture;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

import components.Bus;
import components.Memory;
import components.Register;
import components.Ula;
import components.Demux;

public class Architecture {

  private boolean simulation; // this boolean indicates if the execution is done in simulation mode.
                              // simulation mode shows the components' status after each instruction

  private boolean halt;
  private Bus extBus1;
  private Bus intBus1;
  private Bus intBus2;
  private Bus statusBus;
  private Memory memory;
  private Memory statusMemory;
  private int memorySize;
  private Register pc;
  private Register ir;
  private Register RPG0;
  private Register RPG1;
  private Register RPG2;
  private Register RPG3;
  private Register stackTop;
  private Register stackBottom;
  private Register flags;
  private Ula ula;
  private Demux demux; // only for multiple register purposes

  private ArrayList<String> commandsList;
  private ArrayList<Register> registersList;

  /**
   * Instantiates all components in this architecture
   */
  private void componentsInstances() {
    // don't forget the instantiation order
    // buses -> registers -> ula -> memory
    extBus1 = new Bus();
    intBus1 = new Bus();
    intBus2 = new Bus();
    statusBus = new Bus();
    pc = new Register("pc", extBus1, intBus1);
    ir = new Register("ir", extBus1, intBus2);
    RPG0 = new Register("RPG0", extBus1, intBus1);
    RPG1 = new Register("RPG1", extBus1, intBus1);
    RPG2 = new Register("RPG2", extBus1, intBus1);
    RPG3 = new Register("RPG3", extBus1, intBus1);
    stackTop = new Register("stackTop", extBus1, intBus1);
    stackBottom = new Register("stackBottom", extBus1, intBus1);
    flags = new Register(2, statusBus);
    fillRegistersList();
    ula = new Ula(intBus1, intBus2);
    statusMemory = new Memory(2, intBus2);
    memorySize = 128;
    memory = new Memory(memorySize, extBus1);
    demux = new Demux(); // this bus is used only for multiple register operations

    fillCommandsList();
  }

  /**
   * This method fills the registers list inserting into them all the registers we
   * have.
   * IMPORTANT!
   * The first register to be inserted must be the default RPG0
   */
  private void fillRegistersList() {
    registersList = new ArrayList<Register>();
    registersList.add(RPG0);
    registersList.add(RPG1);
    registersList.add(RPG2);
    registersList.add(RPG3);
    registersList.add(stackTop);
    registersList.add(stackBottom);
    registersList.add(pc);
    registersList.add(ir);
    registersList.add(flags);
  }

  /**
   * Constructor that instantiates all components according the architecture
   * diagram
   */
  public Architecture() {
    componentsInstances();

    // by default, the execution method is never simulation mode
    simulation = false;
  }

  public Architecture(boolean sim) {
    componentsInstances();

    // in this constructor we can set the simulation mode on or off
    simulation = sim;
  }

  // getters

  protected Bus getExtBus1() {
    return extBus1;
  }

  protected Bus getIntBus1() {
    return intBus1;
  }

  protected Bus getIntBus2() {
    return intBus2;
  }

  protected Memory getMemory() {
    return memory;
  }

  protected Register getPc() {
    return pc;
  }

  protected Register getIr() {
    return ir;
  }

  protected Register getRPG0() {
    return RPG0;
  }

  protected Register getRPG1() {
    return RPG1;
  }

  protected Register getRPG2() {
    return RPG2;
  }

  protected Register getRPG3() {
    return RPG3;
  }

  protected Register getStackTop() {
    return stackTop;
  }

  protected Register getStackBottom() {
    return stackBottom;
  }

  protected Register getFlags() {
    return flags;
  }

  protected Demux getDemux() {
    return demux;
  }

  protected Ula getUla() {
    return ula;
  }

  public ArrayList<String> getCommandsList() {
    return commandsList;
  }

  // all the microprograms must be implemented here
  /**
   * This method fills the commands list arraylist with all commands used in this
   * architecture
   */
  protected void fillCommandsList() {
    commandsList = new ArrayList<String>();
    commandsList.add("addRegReg"); // 0
    commandsList.add("addMemReg"); // 1
    commandsList.add("addRegMem"); // 2
    commandsList.add("addImmReg"); // 3
    commandsList.add("subRegReg"); // 4
    commandsList.add("subMemReg"); // 5
    commandsList.add("subRegMem"); // 6
    commandsList.add("subImmReg"); // 7
    commandsList.add("moveMemReg"); // 8
    commandsList.add("moveRegMem"); // 9
    commandsList.add("moveRegReg"); // 10
    commandsList.add("moveImmReg"); // 11
    commandsList.add("incReg"); // 12
    commandsList.add("jmp"); // 13
    commandsList.add("jn"); // 14
    commandsList.add("jz"); // 15
    commandsList.add("jeq"); // 16
    commandsList.add("jneq"); // 17
    commandsList.add("jgt"); // 18
    commandsList.add("jlw"); // 19
    commandsList.add("call"); // 20
    commandsList.add("ret"); // 21
  }

  /**
   * This method is used after some ULA operations, setting the flags bits
   * according the result.
   * 
   * @param result is the result of the operation
   *               NOT TESTED!!!!!!!
   */
  private void setStatusFlags(int result) {
    flags.setBit(0, 0);
    flags.setBit(1, 0);
    if (result == 0) { // bit 0 in flags must be 1 in this case
      flags.setBit(0, 1);
    }
    if (result < 0) { // bit 1 in flags must be 1 in this case
      flags.setBit(1, 1);
    }
  }

  public void addRegReg() {
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();
    memory.read(); //get first value
    demux.setValue(extBus1.get()); 
    registersInternalRead();
    ula.store(0);
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();
    memory.read(); //get second value
    demux.setValue(extBus1.get()); // seta no demux a referência do registrador que queremos obter o dado
    registersInternalRead();
    ula.store(1);
    ula.add(); // add values
    ula.read(1); // result is in the internalBus1
    setStatusFlags(intBus1.get()); // defines flags after add operation
    registersInternalStore();
    pc.internalRead();  // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
  }

  public void addMemReg() {
    pc.internalRead(); // início de pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read(); 
    memory.read();
    memory.read(); //pegar o primeiro valor da memória
    ir.store(); //Ir armazena valor de extBus1
    ir.internalRead(); // joga valor de IR em intBus2 para ULA pegar
    ula.internalStore(0); // ula pega valor de intBus2 e seu registrador interno 0 armazena
    pc.internalRead(); // pc++
    ula.store(1); 
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();
    memory.read(); // pegar o segundo valor da memória e joga em extBus1
    demux.setValue(extBus1.get()); // seta no demux o valor de extBus1
    registersInternalRead();
    ula.store(1);
    ula.add(); // soma os valores e coloca no segundo registrador da ULA
    ula.read(1); // como o resultado está no segundo registrador, iremos dar um read(1) para que ele jogue seu valor no barramento
    setStatusFlags(intBus1.get()); // atualiza flags
    registersInternalStore();
    pc.internalRead();  // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
  }

  public void addRegMem() {
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();
    memory.read(); //pegar o primeiro valor da memória
    demux.setValue(extBus1.get()); // seta valor de extBus 1 em demux
    registersInternalRead(); // obtém valor do registrador correspondente
    ula.store(0); // armazena no primeiro registrador o valor do barramento
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();
    memory.read();
    memory.read(); //pegar o segundo valor da memória
    ir.store(); //armazena valor de extBus1
    ir.internalRead(); // jogar valor em intBus2
    ula.internalStore(1);  // pega valor de intBus2 e joga em intBus1
    ula.add(); // realiza a operação de soma e armazena no segundo registrador
    ula.internalRead(1); // o valor está no segundo registrador da ula, ela joga para intBus2 e intBus1
    ir.internalStore(); // ir pega o valor de intbus2
    setStatusFlags(intBus2.get()); // atualiza a flag
    pc.read(); // joga valor em extBus1
    memory.read(); // memôria lê e coloca no barramento extBus1
    memory.store(); // lê do barramento a posição onde o valor será armazenado
    ir.read(); // recuperamos o valor de IR e jogamos em extBus1
    memory.store(); // agora armazenamos efetivamente o valor no endereço de memória desejado
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
  }

  public void addImmReg() {
    pc.internalRead();  // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();  // primeiro valor
    memory.read();
    ir.store();
    ir.internalRead();
    ula.internalStore(0);
    pc.internalRead(); //pc++
    ula.store(1);
    ula.inc();
    ula.read(1); 
    pc.internalStore();
    pc.read(); //segundo valor
    memory.read();
    demux.setValue(extBus1.get());
    registersInternalRead();
    ula.store(1);
    ula.add();
    ula.internalRead(1);
    setStatusFlags(intBus2.get());
    ula.read(1);
    registersInternalStore();
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
  }

  public void subRegReg() {
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read(); // obtém o primeiro valor
    memory.read();
    demux.setValue(extBus1.get()); //seta valor de extBus 1 em demux
    registersInternalRead();
    ula.store(0);
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read(); // obtém o segundo valor a ser utilizado
    memory.read();
    demux.setValue(extBus1.get());
    registersInternalRead();
    ula.store(1);
    ula.sub(); // operação de subtração
    ula.read(1); 
    setStatusFlags(intBus1.get()); // atualiza a flag
    registersInternalStore();
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
  }

  public void subMemReg() {
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();
    memory.read(); 
    memory.read(); // obtém o primeiro valor
    ir.store();
    ir.internalRead();
    ula.internalStore(0);
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();
    memory.read(); // obtém o segundo valor a ser utilizado
    demux.setValue(extBus1.get()); // seta no demux a referência do registrador que queremos obter o dado
    registersInternalRead();
    ula.store(1);
    ula.sub(); // realiza-se a subtração e o resultado fica no segundo registrador
    ula.read(1); // como o resultado está no segundo registrador, iremos dar um read(1) para que ele jogue seu valor no barramento, intBus1
    setStatusFlags(intBus1.get()); // atualiza a flag
    registersInternalStore();
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
  }

  public void subRegMem() {
    // pc++
    pc.internalRead();
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    // obtém o primeiro valor
    pc.read();
    memory.read();
    demux.setValue(extBus1.get()); // seta no demux a referência do registrador que queremos obter o dado
    registersInternalRead();
    ula.store(0);
    // pc++
    pc.internalRead();
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    // obtém o segundo valor a ser utilizado
    pc.read();
    memory.read();
    memory.read();
    ir.store();
    ir.internalRead();
    ula.internalStore(1);
    // operação
    ula.sub(); // realiza-se a subtração e o resultado fica no segundo registrador
    ula.internalRead(1);
    ir.internalStore();
    setStatusFlags(intBus2.get()); // atualiza a flag
    // armazena na memória
    pc.read();
    memory.read();
    memory.store();
    ir.read();
    memory.store();
    // pc++
    pc.internalRead();
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
  }

  public void subImmReg() {
    //pc++
    pc.internalRead();
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();

    // primeiro valor
    pc.read();
    memory.read();
    ir.store();
    ir.internalRead();
    ula.internalStore(0);

    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();
    memory.read();
    demux.setValue(extBus1.get());
    registersInternalRead();
    ula.store(1);
    ula.sub();
    ula.internalRead(1);
    setStatusFlags(intBus2.get());
    ula.read(1);
    registersInternalStore();
    
    //pcc+
    pc.internalRead();
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
  }

  public void moveMemReg() {
    // pc++
    pc.internalRead();
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    // obtém o primeiro valor
    pc.read();
    memory.read();
    memory.read();
    ir.store();
    // pc++
    pc.internalRead();
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore(); 
    pc.read(); 
    memory.read(); // obtém o segundo valor a ser utilizado
    demux.setValue(extBus1.get()); // seta no demux a referência do registrador que queremos obter o dado
    ir.read();
    registersStore(); // armazena o dado no registrador com identificador correspondente no demux
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore(); // ao final PC ira apontar para a próxima instrução
  }

  public void moveRegMem() {
    pc.internalRead();  // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();
    memory.read();
    demux.setValue(extBus1.get()); // seta no demux a referência do registrador que queremos obter o dado
    registersRead(); // obtém o primeiro valor
    ir.store();
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore(); 
    pc.read();
    memory.read();
    memory.store(); // obtém o segundo valor
    ir.read();
    memory.store();
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore(); // pc irá apontar para a próxima instrução
  }

  public void moveRegReg() {
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();
    memory.read();
    demux.setValue(extBus1.get()); // seta no demux a referência do registrador que queremos obter o dado
    registersRead();
    ir.store();
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore(); 
    pc.read();
    memory.read();
    demux.setValue(extBus1.get()); // seta no demux a referência do registrador que queremos obter o dado
    ir.read();
    registersStore(); // armazena o dado no demux com identificador correspondente n
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore(); // pc irá apontar para a próxima instrução
  }

  public void moveImmReg() {
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();
    memory.read();
    ir.store();
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore(); 
    pc.read();
    memory.read();
    demux.setValue(extBus1.get()); // seta no demux a referência do registrador que queremos obter o dado
    ir.read();
    registersStore(); // armazena o dado no demux com identificador correspondente n
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
  }

  public void incReg() {
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();
    memory.read();
    demux.setValue(extBus1.get()); // seta no demux a referência do registrador que queremos obter o dado
    registersInternalRead();
    ula.store(1);
    ula.inc();
    ula.read(1);
    registersInternalStore();
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
  }

  public void jmp() {
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore(); 
    pc.read();
    memory.read();
    pc.store();
  }

  public void jn() {
    pc.internalRead(); //pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();
    memory.read();
    ir.store();
    ir.internalRead();
    statusMemory.storeIn1();
    ula.inc();
    ula.internalRead(1);
    statusMemory.storeIn0();
    intBus2.put(flags.getBit(1));
    statusMemory.read();
    ir.internalStore();
    ir.read();
    pc.store();
  }

  public void jz() {
    pc.internalRead();
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();
    memory.read();
    ir.store();
    ir.internalRead();
    statusMemory.storeIn1();
    ula.inc();
    ula.internalRead(1);
    statusMemory.storeIn0();
    intBus2.put(flags.getBit(0));
    statusMemory.read();
    ir.internalStore();
    ir.read();
    pc.store();
  }

  public void jeq() {
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();
    memory.read();
    demux.setValue(extBus1.get());
    registersInternalRead();
    ula.store(0);
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();
    memory.read();
    demux.setValue(extBus1.get());
    registersInternalRead();
    ula.store(1);
    ula.sub();
    ula.read(1);
    setStatusFlags(intBus1.get());
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();
    memory.read();
    ir.store();
    ir.internalRead();
    statusMemory.storeIn1();
    pc.internalRead();  // pc++
    ula.store(1);
    ula.inc();
    ula.internalRead(1);
    statusMemory.storeIn0();
    intBus2.put(flags.getBit(0)); 
    statusMemory.read();
    ir.internalStore();
    ir.read();
    pc.store();
  }

  public void jneq() {
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();
    memory.read(); // lê valor e joga em extBus1
    demux.setValue(extBus1.get()); // demux guarda identificador do registrador que queremos obter o valor
    registersInternalRead();
    ula.store(0); // guarda valor no registrador 0 da ULA
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();
    memory.read();
    demux.setValue(extBus1.get()); // demux guarda identificador do registrador que queremos obter o valor
    registersInternalRead(); // obtém valor do registrador que queremos
    ula.store(1);
    ula.sub();
    ula.read(1);
    setStatusFlags(intBus1.get()); //atualiza status das flags
    pc.internalRead(); // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();
    memory.read();
    ir.store();
    ir.internalRead();
    statusMemory.storeIn1(); // armazena o endereço que queremos seguir
    pc.internalRead();  // pc++
    ula.store(1);
    ula.inc(); //incrementa o dado do segundo registrador da ULA
    ula.internalRead(1);
    statusMemory.storeIn0();
    intBus2.put(flags.getBit(1)); 
    statusMemory.read();
    ir.internalStore(); // dá um internal store para pegar o dado da statusMemory q está em intBus2
    ir.read(); // joga dado em extBus1
    pc.store(); // pc pega o dado de extBus1
  }

  public void jgt() {
    pc.internalRead();  // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();
    memory.read();
    demux.setValue(extBus1.get());
    registersInternalRead();
    ula.store(0);
    pc.internalRead();  // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();
    memory.read();
    demux.setValue(extBus1.get());
    registersInternalRead();
    ula.store(1);
    ula.sub();
    ula.read(1);
    setStatusFlags(intBus1.get());
    intBus1.put(flags.getBit(0));
    ula.store(0);
    intBus1.put(flags.getBit(1));
    ula.store(1);
    ula.add();
    ula.read(1);
    setStatusFlags(intBus1.get());
    pc.internalRead();  // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();
    memory.read();
    ir.store();
    ir.internalRead();
    statusMemory.storeIn1();
    pc.internalRead();  // pc++
    ula.store(1);
    ula.inc();
    ula.internalRead(1);
    statusMemory.storeIn0();
    intBus2.put(flags.getBit(0));
    statusMemory.read();
    ir.internalStore();
    ir.read();
    pc.store();
  }

  public void jlw() {
    pc.internalRead();  // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();
    memory.read();
    demux.setValue(extBus1.get());
    registersInternalRead();
    ula.store(0);
    pc.internalRead();  // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();
    memory.read();
    demux.setValue(extBus1.get());
    registersInternalRead();
    ula.store(1);
    ula.sub();
    ula.read(1);
    setStatusFlags(intBus1.get());
    intBus1.put(flags.getBit(0));
    ula.store(0);
    intBus1.put(flags.getBit(1));
    ula.store(1);
    ula.sub();
    ula.read(1);
    setStatusFlags(intBus1.get());
    pc.internalRead();  // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read();
    memory.read();
    ir.store();
    ir.internalRead();
    statusMemory.storeIn1();
    pc.internalRead();  // pc++
    ula.store(1);
    ula.inc();
    ula.internalRead(1);
    statusMemory.storeIn0();
    intBus2.put(flags.getBit(1));
    statusMemory.read();
    ir.internalStore();
    ir.read();
    pc.store();
  }

  public void call() {
    pc.internalRead();  // pc++
    ula.store(1);
    ula.inc();
    ula.read(1);
    pc.internalStore();
    pc.read(); // joga valor para extBus1
    memory.read(); // memoria lê dado de extBus1
    ir.store(); // ir armazenada dado de  extBus1
    ir.internalRead(); // ir joga dado em intBus2
    ula.internalStore(0); // ula pega dado de intBus2 e joga em intBus1
    stackTop.read(); // joga seu dado em extBus1
    memory.store(); // inicio do store 
    ula.inc(); // ula incrementa
    ula.internalRead(1); // ula joga valor em intBus1 e tambem em intBus2
    ir.internalStore(); // ir armazena dado de intBus2
    ir.read(); // ir joga o valor em em extBus1
    memory.store(); // memoria lê dado de endereço de extBus1
    ula.read(0); // ula joga o dado em intBus1
    pc.internalStore(); // pc armazena dado de intBus1
    stackTop.internalRead(); // stackTop joga dado em intBus1
    ula.store(0); //ula armazena no primeiro registrador
    intBus1.put(1); //
    ula.store(1);
    ula.sub(); //subtrair o endereço em uma unidade pos memória vai de 0 - 127
    ula.read(1); // ula joga para intBus1
    stackTop.internalStore();// stackTop consome de intBus1
  }

  public void ret() {
    stackTop.internalRead(); // joga o dado em intBus1
    ula.store(1); // pega o dado de intBus1
    ula.inc(); // incrementa e armazena nos segundo registrador de ula
    ula.read(1); // joga para intbus1 o resultado
    stackTop.internalStore(); // pega o dado de intBus1
    stackTop.read(); // joga o dado em extBus1
    memory.read(); //memôria lê o dado de extbus1
    pc.store(); // pc aponta para a próxima instrução
  }

  public ArrayList<Register> getRegistersList() {
    return registersList;
  }

  /**
   * This method performs an (external) read from a register into the register
   * list.
   * The register id must be in the demux bus
   */
  protected void registersRead() {
    registersList.get(demux.getValue()).read();
  }

  /**
   * This method performs an (internal) read from a register into the register
   * list.
   * The register id must be in the demux bus
   */
  protected void registersInternalRead() {
    registersList.get(demux.getValue()).internalRead();
  }

  /**
   * This method performs an (external) store toa register into the register list.
   * The register id must be in the demux bus
   */
  protected void registersStore() {
    registersList.get(demux.getValue()).store();
  }

  /**
   * This method performs an (internal) store toa register into the register list.
   * The register id must be in the demux bus
   */
  protected void registersInternalStore() {
    registersList.get(demux.getValue()).internalStore();
    ;
  }

  /**
   * This method reads an entire file in machine code and
   * stores it into the memory
   * NOT TESTED
   * 
   * @param filename
   * @throws IOException
   */
  public void readExec(String filename) throws IOException {
    BufferedReader br = new BufferedReader(new FileReader(filename + ".dxf"));
    String linha;
    int i = 0;
    while ((linha = br.readLine()) != null) {
      extBus1.put(i);
      memory.store();
      extBus1.put(Integer.parseInt(linha));
      memory.store();
      i++;
    }
    br.close();
  }

  /**
   * This method executes a program that is stored in the memory
   */
  public void controlUnitExec() {
    halt = false;
    while (!halt) {
      fetch();
      decodeExecute();
    }

  }

  /**
   * This method implements The decode process,
   * that is to find the correct operation do be executed
   * according the command.
   * And the execute process, that is the execution itself of the command
   */
  private void decodeExecute() {
    ir.internalRead(); // the instruction is in the internalBus2
    int command = intBus2.get();
    simulationDecodeExecuteBefore(command);
    switch (command) {
      case 0:
        addRegReg();
        break;
      case 1:
        addMemReg();
        break;
      case 2:
        addRegMem();
        break;
      case 3:
        addImmReg();
        break;
      case 4:
        subRegReg();
        break;
      case 5:
        subMemReg();
        break;
      case 6:
        subRegMem();
        break;
      case 7:
        subImmReg();
        break;
      case 8:
        moveMemReg();
        break;
      case 9:
        moveRegMem();
        break;
      case 10:
        moveRegReg();
        break;
      case 11:
        moveImmReg();
        break;
      case 12:
        incReg();
        break;
      case 13:
        jmp();
        break;
      case 14:
        jn();
        break;
      case 15:
        jz();
        break;
      case 16:
        jeq();
        break;
      case 17:
        jneq();
        break;
      case 18:
        jgt();
        break;
      case 19:
        jlw();
        break;
      case 20:
        call();
        break;
      case 21:
        ret();
        break;
      default:
        halt = true;
        break;
    }
    if (simulation)
      simulationDecodeExecuteAfter();
  }

  /**
   * This method is used to show the components status in simulation conditions
   * NOT TESTED
   * 
   * @param command
   */
  private void simulationDecodeExecuteBefore(int command) {
    System.out.println("----------BEFORE Decode and Execute phases--------------");
    String instruction;
    int parameter = 0;
    for (Register r : registersList) {
      System.out.println(r.getRegisterName() + ": " + r.getData());
    }
    if (command != -1)
      instruction = commandsList.get(command);
    else
      instruction = "END";
    if (hasOperands(instruction)) {
      parameter = memory.getDataList()[pc.getData()+1];
      System.out.println("Instruction: " + instruction + " " + parameter);
    } else
      System.out.println("Instruction: " + instruction);
    if ("read".equals(instruction))
      System.out.println("memory[" + parameter + "]=" + memory.getDataList()[parameter]);
  }

  /**
   * This method is used to show the components status in simulation conditions
   * NOT TESTED
   */
  private void simulationDecodeExecuteAfter() {
    try {
      System.out.println("-----------AFTER Decode and Execute phases--------------");
      System.out.println("Internal Bus 1: " + intBus1.get());
      System.out.println("Internal Bus 2: " + intBus2.get());
      System.out.println("External Bus 1: " + extBus1.get());
      for (Register r : registersList) {
        System.out.println(r.getRegisterName() + ": " + r.getData());
      }

      // Thread.sleep(2000); 
    } catch (Exception e) {
      System.out.println(e);
    }
    Scanner entrada = new Scanner(System.in);
    System.out.println("Press <Enter>");
    String mensagem = entrada.nextLine();
  }

  /**
   * This method uses pc to find, in the memory,
   * the command code that must be executed.
   * This command must be stored in ir
   * NOT TESTED!
   */
  private void fetch() {
    pc.read();
    memory.read();
    ir.store();
    simulationFetch();
  }

  /**
   * This method is used to show the components status in simulation conditions
   * NOT TESTED!!!!!!!!!
   */
  private void simulationFetch() {
    if (simulation) {
      System.out.println("-------Fetch Phase------");
      System.out.println("pc: " + pc.getData());
      System.out.println("ir: " + ir.getData());
    }
  }

  /**
   * This method is used to show in a correct way the operands (if there is any)
   * of instruction,
   * when in simulation mode
   * NOT TESTED!!!!!
   * 
   * @param instruction
   * @return
   */
  private boolean hasOperands(String instruction) {
    if ("inc".equals(instruction)) // inc is the only one instruction having no operands
      return false;
    else
      return true;
  }

  /**
   * This method returns the amount of positions allowed in the memory
   * of this architecture
   * NOT TESTED!!!!!!!
   * 
   * @return
   */
  public int getMemorySize() {
    return memorySize;
  }

  public static void main(String[] args) throws IOException {
    Architecture arch = new Architecture(true);
    arch.readExec("program");
    arch.controlUnitExec();
  }
}