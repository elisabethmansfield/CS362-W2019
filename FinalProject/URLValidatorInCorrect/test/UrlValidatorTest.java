/******************************************************************************
 *
 * Assignment: Final Project Part B
 * Group Members: Laura Lund, lundl
 *  Elisabeth Mansfield, mansfiee
 *  Graham Roese, roeseg
 * Description:
 *  - ManualTestInterface allows a user to input a url string,
 *  indicate whether it is valid, and then compare the result of calling
 *  isValid() with the expected result. Because JUnit hangs on user input,
 *  manual testing must be run separately from the other tests. To run
 *  manual tests, run ManualTestInterface main() and type input into the
 *  console.
 *  - Random Testing tests a randomly-selected number of instances of the
 *  UrlValidator method isValid() by partitioning the set of possible inputs
 *  into two subdomains, Scheme + Host and Scheme + Host + Path + Query and
 *  passing as input a URL that is randomly constructed from five pre-defined sets.
 *  - Programming Based Testing
 *****************************************************************************/

import junit.framework.AssertionFailedError;
import junit.framework.TestCase;
//import org.junit.Test;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.util.Random;

public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   /**************************************************************************
    * Author: Laura Lund, lundl@oregonstate.edu
    * Description: This function simulates manual testing of UrlValidator
    * isValid(). URLs to be tested are individually used as parameters for
    * calls to isValid(). The result of this call is compared to the expected
    * result for each URL. If the actual result and the expected result match,
    * the test case for that URL passes. If they do not match, the test case
    * for that URL fails. If any one test case fails, testManualTest fails.
    * ***********************************************************************/
   public void testManualTest()
   {
      System.out.println("\n-----Begin Manual Testing-----");
      // Explicitly manual testing is implemented in ManualTestInterface
      // Simulated manual testing is implemented here to be run with JUnit
      boolean didPass = true;

      // This hash map holds urls to be tested and a value of whether they are valid
      Map<String, Boolean> urlsToTest = new HashMap<String, Boolean>();

      /* Valid Urls */
      // IP Address
      urlsToTest.put("http://172.217.11.164", true);

      // Host Names alone
      urlsToTest.put("http://www.google.com", true);
      urlsToTest.put("http://google.com", true);
      urlsToTest.put("http://oregonstate.edu", true);
      urlsToTest.put("http://www.iana.org", true);
      urlsToTest.put("http://somedomain.net", true);
      urlsToTest.put("http://www.somedomain.net", true);


      // Sub Domains
      urlsToTest.put("http://engineering.oregonstate.edu", true);
      urlsToTest.put("http://en.somedomain.net", true);

      // Port Numbers
      urlsToTest.put("http://www.google.com:80", true);
      urlsToTest.put("http://google.com:80", true);
      urlsToTest.put("http://172.217.11.164:80", true);


      // Paths and Fragments
      urlsToTest.put("http://www.iana.org/page.html#bookmark", true);
      urlsToTest.put("http://www.iana.org/domains/root", true);
      urlsToTest.put("http://en.somedomain.net/dir/page.html#bookmark", true);
      urlsToTest.put("http://www.somedomain.net/page.html#bookmark", true);
      urlsToTest.put("http://somedomain.net/dir1/dir2/dir3/dir4/dir5/", true);
      urlsToTest.put("http://somedomain.net/dir1/dir2/dir3/dir4/dir5", true);


      // Other Schemes
      urlsToTest.put("https://www.google.com", true);
      urlsToTest.put("ftp://www.google.com", true);
      urlsToTest.put("file://www.google.com", true);
      urlsToTest.put("telnet://www.google.com", true);
      urlsToTest.put("https://www.reddit.com/r/cscareerquestions/comments/azqbr4/interview_discussion_march_11_2019/", true);

      // Queries
      urlsToTest.put("http://somedomain.net?firstname=Laura&lastname=Lund", true);
      urlsToTest.put("http://www.somedomain.net?firstname=Laura&lastname=Lund", true);
      urlsToTest.put("http://www.somedomain.net?firstname=Laura", true);
      urlsToTest.put("http://subdomain.somedomain.net?firstname=Laura&lastname=Lund", true);


      /* Invalid Urls */

      // Too Long Host Name
      urlsToTest.put("http://www.thisismyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallylonghostname.org", false);
      urlsToTest.put("www.thisismyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallylonghostname.org", false);

      // Empty Scheme
      urlsToTest.put("172.217.11.164:80", false);
      urlsToTest.put("google.com", false);
      urlsToTest.put("www.google.com", false);
      urlsToTest.put("www.google.com:80", false);
      urlsToTest.put("www.oregonstate.edu", false);
      urlsToTest.put("oregonstate.edu", false);
      urlsToTest.put("oregonstate.edu:80", false);
      urlsToTest.put("engineering.oregonstate.edu", false);
      urlsToTest.put("engineering.oregonstate.edu:80", false);
      urlsToTest.put("172.217.11.164", false);
      urlsToTest.put("www.iana.org", false);
      urlsToTest.put("somedomain.garbage", false);
      urlsToTest.put("www.reddit.com/r/cscareerquestions/comments/azqbr4/interview_discussion_march_11_2019/", false);

      // Bad TLD
      urlsToTest.put("http://somedomain.garbage", false);

      // Missing Host Name
      urlsToTest.put("org", false);
      urlsToTest.put(".com", false);
      urlsToTest.put("http://org", false);

      // Bad Port Number
      urlsToTest.put("http://www.google.com:-1", false);
      urlsToTest.put("www.google.com:-1", false);

      // Bad Path
      urlsToTest.put("http://somedomain.net//dir1/", false);
      urlsToTest.put("http://www.iana.orgdomains/root", false);
      urlsToTest.put("www.iana.orgdomains/root", false);

      // Bad Query
      urlsToTest.put("http://subdomain.somedomain.net? firstname=Laura&lastname=Lund", false);
      urlsToTest.put("http://www.somedomain.net?firstname=Laura?lastname=Lund", false);
      urlsToTest.put("http://www.somedomain.netfirstname=Laura", false);

      // Bad IP Address
      urlsToTest.put("255.255.255.256", false);
      urlsToTest.put("http://255.255.255.256", false);

      // Bad Scheme
      urlsToTest.put(".http://www.google.com", false);
      urlsToTest.put("//www.google.com", false);
      urlsToTest.put("://www.google.com", false);
      urlsToTest.put("http//www.google.com", false);
      urlsToTest.put("http:/www.google.com", false);
      urlsToTest.put("http/www.google.com", false);
      urlsToTest.put("httpwww.google.com", false);
      urlsToTest.put("https//www.google.com", false);



      // Print values stored in hash map
  /*     for(Map.Entry<String,Boolean> entry : urlsToTest.entrySet()) {
           System.out.println(entry.getKey());
       }
*/
      // Iterate through hash map and test each url
      for(Map.Entry<String,Boolean> entry : urlsToTest.entrySet()) {
         String userURL = entry.getKey();
         boolean userAssertion = entry.getValue();

         // UrlValidator object
         UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

         // Try to validate the user's url
         try {
            boolean result = urlVal.isValid(userURL);
            if (result == userAssertion) {
               System.out.println("PASSED: " + userURL);
            } else {
               System.out.println("FAILED: " + userURL);
               System.out.println("     Expected: " + userAssertion + ", Actual: " + result);
               didPass = false;
            }
         }
         // Catch all errors or exceptions
         catch(Throwable t) {
            System.out.println("FAILED: " + userURL);
            System.out.println("     ERROR or EXCEPTION: " + t);
            didPass = false;
         }
      }

/*
       // Print results of test
       System.out.println("-----Manual Testing Results-----");
       if(didPass) {
           System.out.println("    PASS");
       }
       else {
           System.out.println("    FAIL");
       }
       */
      System.out.println("-----End Manual Testing-----\n");

      // If there were any failing test cases, fail the test
      assertEquals("testManualTest() Result: ", true, didPass);
   }

   /**************************************************************************
    * Author: Elisabeth Mansfield, mansfiee@oregonstate.edu
    * Method: testRandomTest()
    * Description: This function simulates random testing of UrlValidator
    * isValid(). The schemes, hosts, paths, and queries are initialized with
    * their boolean true/false values. Then, the input domain in partitioned
    * into two sets: Scheme + Host and Scheme + Host + Path + Query. This method
    * calls testFirstPartition() and testSecondPartition() on the two subdomains.
    * ***********************************************************************/
   public void testRandomTest()
   {
      System.out.println("\n-----Begin Random Testing-----");

      // These hash maps holds parts of the url to be tested and whether they are valid
      Map<String, Boolean> schemes = new HashMap<String, Boolean>();
      Map<String, Boolean> hosts = new HashMap<String, Boolean>();
      Map<String, Boolean> paths = new HashMap<String, Boolean>();
      Map<String, Boolean> queries = new HashMap<String, Boolean>();

      // Valid Schemes
      schemes.put("http://",true);
      schemes.put("ftp://",true);
      schemes.put("file://",true);
      schemes.put("https://",true);
      schemes.put("telnet://",true);

      // Invalid Schemes
      schemes.put("http:/",false);
      schemes.put("://",false);
      schemes.put("http/",false);
      schemes.put("http//",false);
      schemes.put("/",false);

      // Valid Host Names, Ports & IP Addresses
      hosts.put("www.myschool.edu",true);
      hosts.put("myschool.edu",true);
      hosts.put("cs.myschool.edu",true);
      hosts.put("cs.myschool.edu:80",true);
      hosts.put("172.217.11.164",true);

      // Invalid Host Names, Ports & IP Addresses
      hosts.put("www.thisismyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallylonghostname.org",false);
      hosts.put("mywebsite.garbage",false);
      hosts.put("org",false);
      hosts.put(".com",false);
      hosts.put("myschool.edu:-1",false);
      hosts.put("255.255.255.256",false);

      // Valid Paths
      paths.put("/",true);
      paths.put("/cs",true);
      paths.put("/cs/",true);
      paths.put("/cs/courses",true);
      paths.put("/cs/courses/list.html",true);
      paths.put("/cs/courses/list.html#fall%20term",true);
      paths.put("",true);

      // Invalid Paths
      paths.put("cs",false);
      paths.put("cs/",false);
      paths.put("cs/courses/list.html#fall term",false);
      paths.put("//",false);

      // Valid Queries
      queries.put("?field=2",true);
      queries.put("?firstname=Laura&lastname=Lund",true);
      queries.put("",true);

      // Invalid Queries
      queries.put("field=2",false);
      queries.put("? problem=space",false);
      queries.put("?marks=2?valid=false",false);

      // test first partition: Scheme + Host
      boolean pass1 = testFirstPartition(schemes,hosts);
      // test second partition: Scheme + Host + Path + Query
      boolean pass2 = testSecondPartition(schemes,hosts,paths,queries);

      // If there were any failing test cases, fail the test
      System.out.println("-----End Random Testing-----\n");
      boolean didPass = pass1 && pass2;
      assertEquals("testRandomTest() Result: ", true, didPass);
   }

   /**************************************************************************
    * Author: Elisabeth Mansfield, mansfiee@oregonstate.edu
    * Method: testFirstPartition()
    * Description: This function simulates random testing of UrlValidator
    * isValid() on the first subdomain of all possible inputs, Scheme + Host.
    * It randomly chooses a number of tests to execute in the range [10-100].
    * The URL is randomly constructed of a Scheme + Host that are randomly
    * chosen from the input hash maps. The expected boolean result is constructed
    * by a logical AND operation. Then, the constructed URL is passed to an
    * instance of UrlValidator and checked for pass/fail result.
    * ***********************************************************************/
   public boolean testFirstPartition(Map<String, Boolean> schemes,Map<String, Boolean> hosts)
   {
      // actual test result
      boolean didPass = true;

      // randomly select number of tests [10-100]
      Random r = new Random();
      int numTests = r.nextInt((100 - 10) + 1) + 10;
      System.out.println("\n-----First Partition: Scheme + Host: "+numTests+" Tests-----");

      // Test URLs for a random number of tests
      for(int i=0; i<numTests; i++) {

         // select random scheme
         String[] schemes_keys = schemes.keySet().toArray(new String[0]);
         String randomScheme = (String) schemes_keys[r.nextInt(schemes_keys.length)];
         boolean schemeBool = schemes.get(randomScheme);

         // select random host
         String[] hosts_keys = hosts.keySet().toArray(new String[0]);
         String randomHost = (String) hosts_keys[r.nextInt(hosts_keys.length)];
         boolean hostBool = hosts.get(randomHost);

         // compose random url
         String userURL = randomScheme + randomHost;
         boolean userAssertion = schemeBool && hostBool;

         // instance of UrlValidator
         UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

         // Try to validate the user's url
         try {
            boolean result = urlVal.isValid(userURL);
            if (result == userAssertion) {
               System.out.println("PASSED: " + userURL);
            } else {
               System.out.println("FAILED: " + userURL);
               System.out.println("     Expected: " + userAssertion + ", Actual: " + result);
               didPass = false;
            }
         }
         // Catch all errors or exceptions
         catch(Throwable t) {
            System.out.println("FAILED: " + userURL);
            System.out.println("     ERROR or EXCEPTION: " + t);
            didPass = false;
         }
      }

      System.out.println("-----End First Partition-----\n");

      return didPass;
   }

   /**************************************************************************
    * Author: Elisabeth Mansfield, mansfiee@oregonstate.edu
    * Method: testSecondPartition()
    * Description: This function simulates random testing of UrlValidator
    * isValid() on the second subdomain of all possible inputs, Scheme + Host +
    * Path + Query. It randomly chooses a number of tests to execute in the
    * range [10-100]. The URL is randomly constructed of a Scheme + Host + Path + Query
    * that are randomly chosen from the input hash maps. The expected boolean result
    * is constructed by a logical AND operation. Then, the constructed URL is
    * passed to an instance of UrlValidator and checked for pass/fail result.
    * ***********************************************************************/
   public boolean testSecondPartition(Map<String, Boolean> schemes,Map<String, Boolean> hosts,
                                   Map<String, Boolean> paths,Map<String, Boolean> queries)
   {
      // actual test result
      boolean didPass = true;

      // randomly select number of tests [10-100]
      Random r = new Random();
      int numTests = r.nextInt((100 - 10) + 1) + 10;
      System.out.println("-----Second Partition: Scheme + Host + Path + Query: "+numTests+" Tests-----");

      // Test URLs for a random number of tests
      for(int i=0; i<numTests; i++) {

         // select random scheme
         String[] schemes_keys = schemes.keySet().toArray(new String[0]);
         String randomScheme = (String) schemes_keys[r.nextInt(schemes_keys.length)];
         boolean schemeBool = schemes.get(randomScheme);

         // select random host
         String[] hosts_keys = hosts.keySet().toArray(new String[0]);
         String randomHost = (String) hosts_keys[r.nextInt(hosts_keys.length)];
         boolean hostBool = hosts.get(randomHost);

         // select random path
         String[] paths_keys = paths.keySet().toArray(new String[0]);
         String randomPath = (String) paths_keys[r.nextInt(paths_keys.length)];
         boolean pathBool = paths.get(randomPath);

         // select random query
         String[] queries_keys = queries.keySet().toArray(new String[0]);
         String randomQuery = (String) queries_keys[r.nextInt(queries_keys.length)];
         boolean queryBool = queries.get(randomQuery);

         // compose random url
         String userURL;
         boolean userAssertion;
         // some urls have path + query
         if(i % 2 == 0) {
            userURL = randomScheme + randomHost + randomPath + randomQuery;
            userAssertion = schemeBool && hostBool && pathBool && queryBool;
         }
         // some urls only have path
         else {
            userURL = randomScheme + randomHost + randomPath;
            userAssertion = schemeBool && hostBool && pathBool;
         }

         // instance of UrlValidator
         UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

         // Try to validate the user's url
         try {
            boolean result = urlVal.isValid(userURL);
            if (result == userAssertion) {
               System.out.println("PASSED: " + userURL);
            } else {
               System.out.println("FAILED: " + userURL);
               System.out.println("     Expected: " + userAssertion + ", Actual: " + result);
               didPass = false;
            }
         }
         // Catch all errors or exceptions
         catch(Throwable t) {
            System.out.println("FAILED: " + userURL);
            System.out.println("     ERROR or EXCEPTION: " + t);
            didPass = false;
         }
      }

      System.out.println("-----End Second Partition-----\n");

      return didPass;
   }

   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }

   public static void main(String[] argv) {

      UrlValidatorTest fct = new UrlValidatorTest("url test");
      fct.testManualTest();
      fct.testRandomTest();
      fct.testIsValid();
   }

}
