package assembler;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.fail;

import java.util.ArrayList;

import org.junit.Test;

public class testAssembler {
  
  @Test
  public void testAdd(){
		Assembler ass = new Assembler();
		String commandLine[] = new String[3];
		ArrayList<String> returnedObj = new ArrayList<>();
		
		//first test: add
		commandLine[0] = "addRegReg";
		commandLine[1] = "%RPG0";
		commandLine[2] = "%RPG1";

		ass.processCommand(commandLine);
		returnedObj = ass.getObjProgram();

		assertEquals("0", returnedObj.get(0)); //the add code is 0
  }

	//@Test
	public void testRead() {
		fail("Not yet implemented");
	}
}
